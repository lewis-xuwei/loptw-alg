///======================================================
/// Project :   loptw-alg
/// File    :   grb_solver.h
///------------------------------------------------------
/// Time    :   2026/06/26 11:15:10
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#include <memory>
#include <vector>

#include <loptw/instance/instance.h>

#include <gurobi_c++.h>

namespace loptw::grb {

class GRBSolver {
public:
  GRBSolver(std::shared_ptr<instance::Instance> inst);
  ~GRBSolver() = default;
  void AddVariables();
  void AddObjective();
  void AddConstraints();
  void Optimize();

private:
  std::shared_ptr<instance::Instance> inst;
  int T;
  int N;
  int F;

private:
  std::shared_ptr<GRBEnv> env;
  std::shared_ptr<GRBModel> model;

  // ---------- Variables ----------
  std::vector<GRBVar> p;              // p[T]
  std::vector<GRBVar> x;              // x[N]
  std::vector<GRBVar> y;              // y[N]
  std::vector<GRBVar> r;              // r[N]
  std::vector<std::vector<GRBVar>> z; // z[N][T]
  std::vector<std::vector<GRBVar>> l; // lambda[N][N]
  std::vector<std::vector<GRBVar>> m; // mu[N][N]
  std::vector<std::vector<GRBVar>> d; // d[N][N]
  std::vector<std::vector<GRBVar>> a; // alpha[N][N]
  std::vector<std::vector<GRBVar>> b; // beta[N][N]
};

} // namespace loptw::grb
