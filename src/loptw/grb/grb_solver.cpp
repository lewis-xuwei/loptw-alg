///======================================================
/// Project :   loptw-alg
/// File    :   grb_solver.cpp
///------------------------------------------------------
/// Time    :   2026/06/26 11:23:23
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#include <fmt/format.h>

#include <loptw/grb/grb_solver.h>

namespace loptw::grb {

GRBSolver::GRBSolver(std::shared_ptr<instance::Instance> inst) : inst{inst} {
  T = inst->GetNumBuildings();
  N = inst->GetNumTaskNodes();
  F = inst->GetNumWorkflows();

  env = std::make_shared<GRBEnv>(true);
  env->set("LogFile", fmt::format("{}.log", inst->instance_path()));
  env->start();

  model = std::make_shared<GRBModel>(*env);

  cover_inequality_callback = nullptr;
}

void GRBSolver::AddVariables() {
  // p[T]
  p = std::vector<GRBVar>(T);
  for (int t = 0; t < T; ++t) {
    p[t] = model->addVar(0, 1, 0, GRB_BINARY, fmt::format("p_{}", t));
  }

  // x[N]
  x = std::vector<GRBVar>(N);
  for (int i = 0; i < N; ++i) {
    x[i] = model->addVar(0, GRB_INFINITY, 0, GRB_CONTINUOUS, fmt::format("x_{}", i));
  }

  // y[N]
  y = std::vector<GRBVar>(N);
  for (int i = 0; i < N; ++i) {
    y[i] = model->addVar(0, GRB_INFINITY, 0, GRB_CONTINUOUS, fmt::format("y_{}", i));
  }

  // r[N]
  r = std::vector<GRBVar>(N);
  for (int i = 0; i < N; ++i) {
    r[i] = model->addVar(0, 1, 0, GRB_BINARY, fmt::format("r_{}", i));
  }

  // z[N][T]
  z = std::vector<std::vector<GRBVar>>(N, std::vector<GRBVar>(T));
  for (int i = 0; i < N; ++i) {
    for (int t = 0; t < T; ++t) {
      z[i][t] = model->addVar(0, 1, 0, GRB_BINARY, fmt::format("z_{}_{}", i, t));
    }
  }

  // lambda[N][N]
  l = std::vector<std::vector<GRBVar>>(N, std::vector<GRBVar>(N));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      l[i][j] = model->addVar(0, 1, 0, GRB_BINARY, fmt::format("l_{}_{}", i, j));
    }
  }

  // mu[N][N]
  m = std::vector<std::vector<GRBVar>>(N, std::vector<GRBVar>(N));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      m[i][j] = model->addVar(0, 1, 0, GRB_BINARY, fmt::format("m_{}_{}", i, j));
    }
  }

  // d[N][N]
  d = std::vector<std::vector<GRBVar>>(N, std::vector<GRBVar>(N));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      d[i][j] = model->addVar(0, GRB_INFINITY, 0, GRB_CONTINUOUS, fmt::format("d_{}_{}", i, j));
    }
  }
  // alpha[N][N]
  a = std::vector<std::vector<GRBVar>>(N, std::vector<GRBVar>(N));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      a[i][j] = model->addVar(0, GRB_INFINITY, 0, GRB_CONTINUOUS, fmt::format("a_{}_{}", i, j));
    }
  }

  // beta[N][N]}
  b = std::vector<std::vector<GRBVar>>(N, std::vector<GRBVar>(N));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      b[i][j] = model->addVar(0, GRB_INFINITY, 0, GRB_CONTINUOUS, fmt::format("b_{}_{}", i, j));
    }
  }
}

void GRBSolver::AddObjective() {
  GRBLinExpr obj;

  for (int t = 0; t < T; ++t) {
    double rc = inst->buildings().at(t)->rent_cost_;
    obj += rc * p[t];
  }

  for (auto [_, workflow] : inst->workflows()) {
    int i = workflow->source_;
    int j = workflow->target_;
    int f_ij = workflow->quantity_;

    obj += inst->transport_cost() * f_ij * d[i][j];
  }

  model->setObjective(obj, GRB_MINIMIZE);
}

void GRBSolver::AddConstraints() {
  for (int i = 0; i < N; ++i) {
    GRBLinExpr expr;
    for (int t = 0; t < T; ++t) {
      expr += z[i][t];
    }
    model->addConstr(expr == 1, fmt::format("tasknode_placement_{}", i));
  }

  for (int i = 0; i < N; ++i) {
    for (int t = 0; t < T; ++t) {
      model->addConstr(z[i][t] <= p[t], fmt::format("facility_meet_{}", i));
    }
  }

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      double w_i = inst->tasknodes().at(i)->width_;
      double h_i = inst->tasknodes().at(i)->length_;
      double w_j = inst->tasknodes().at(j)->width_;
      double h_j = inst->tasknodes().at(j)->length_;

      model->addConstr(d[i][j] == a[i][j] + b[i][j], fmt::format("distance_{}_{}", i, j));
      model->addConstr(a[i][j] >= (x[i] + 0.5 * w_i * (1 - r[i]) + 0.5 * h_i * r[i])
                                    - (x[j] + 0.5 * w_j * (1 - r[j]) + 0.5 * h_j * r[j]),
                       fmt::format("distance_{}_{}-1", i, j));
      model->addConstr(a[i][j] >= (x[j] + 0.5 * w_j * (1 - r[j]) + 0.5 * h_j * r[j])
                                    - (x[i] + 0.5 * w_i * (1 - r[i]) + 0.5 * h_i * r[i]),
                       fmt::format("distance_{}_{}-2", i, j));
      model->addConstr(b[i][j] >= (y[i] + 0.5 * h_i * (1 - r[i]) + 0.5 * w_i * r[i])
                                    - (y[j] + 0.5 * h_j * (1 - r[j]) + 0.5 * w_j * r[j]),
                       fmt::format("distance_{}_{}-3", i, j));
      model->addConstr(b[i][j] >= (y[j] + 0.5 * h_j * (1 - r[j]) + 0.5 * w_j * r[j])
                                    - (y[i] + 0.5 * h_i * (1 - r[i]) + 0.5 * w_i * r[i]),
                       fmt::format("distance_{}_{}-4", i, j));
    }
  }

  for (int t = 0; t < T; ++t) {
    for (int j = 0; j < N; ++j) {
      for (int i = 0; i < j; ++i) {
        model->addConstr(l[i][j] + l[j][i] + m[i][j] + m[j][i] + (1 - z[i][t]) + (1 - z[j][t]) >= 1,
                         fmt::format("tasknode_relations_{}_{}_{}", i, j, t));
      }
    }
  }

  for (int j = 0; j < N; ++j) {
    for (int i = 0; i < N; ++i) {
      double w_i = inst->tasknodes().at(i)->width_;
      double h_i = inst->tasknodes().at(i)->length_;
      double w_j = inst->tasknodes().at(j)->width_;
      double h_j = inst->tasknodes().at(j)->length_;

      model->addConstr(x[i] + w_i * (1 - r[i]) + h_i * r[i] <= x[j] + 1000000 * (1 - l[i][j]),
                       fmt::format("task-task-right_{}_left_{}", i, j));

      model->addConstr(y[i] + h_i * (1 - r[i]) + w_i * r[i] <= y[j] + 1000000 * (1 - m[i][j]),
                       fmt::format("task-task-top_{}_bottom_{}", i, j));
    }
  }

  for (int t = 0; t < T; ++t) {
    for (int i = 0; i < N; ++i) {
      double w_i = inst->tasknodes().at(i)->width_;
      double h_i = inst->tasknodes().at(i)->length_;
      double W_t = inst->buildings().at(t)->width_;
      double H_t = inst->buildings().at(t)->length_;
      double b_t = inst->buildings().at(t)->bottom_coord_;
      double l_t = inst->buildings().at(t)->left_coord_;

      model->addConstr(x[i] + w_i * (1 - r[i]) + h_i * r[i] <= l_t + W_t + 1000000 * (1 - z[i][t]),
                       fmt::format("task-building-right_{}_right_{}", i, t));

      model->addConstr(x[i] >= l_t - 1000000 * (1 - z[i][t]),
                       fmt::format("task-building-left_{}_left_{}", i, t));

      model->addConstr(y[i] + h_i * (1 - r[i]) + w_i * r[i] <= b_t + H_t + 1000000 * (1 - z[i][t]),
                       fmt::format("task-building-bottom_{}_bottom_{}", i, t));

      model->addConstr(y[i] >= b_t - 1000000 * (1 - z[i][t]),
                       fmt::format("task-building-top_{}_top_{}", i, t));
    }
  }
}

void GRBSolver::Optimize() {
  model->update();
  model->optimize();
}

void GRBSolver::OptimizeWithCoverInequalityCallback() {
  cover_inequality_callback = std::make_unique<CoverInequality>(inst, z);
  model->setCallback(cover_inequality_callback.get(), GRB_CB_MIPSOL);
  model->update();
  model->optimize();
}

} // namespace loptw::grb
