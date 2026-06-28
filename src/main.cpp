#include <iomanip>
#include <iostream>
#include <memory>

#include <fmt/core.h>
#include <fmt/ranges.h>

#include <loptw/grb/grb_solver.h>
#include <loptw/instance/instance.h>

// using namespace std;

// int main(int argc, char* argv[]) {
//   auto instance =
//   loptw::instance::Instance::FromPath("../../data/test1.json"); auto
//   grb_solver = loptw::grb::GRBSolver(instance); grb_solver.AddVariables();
//   grb_solver.AddObjective();
//   grb_solver.AddConstraints();
//   grb_solver.Optimize();
//   return 0;
// }

// #include <alns/ALNS.hpp>
// #include <tsp/DataStructure.h>
// #include <tsp/Point.h>
// #include <tsp/State.h>

// // 导出为动态库或者直接在main函数跑
// tsp::State run_alns_on_state(tsp::DataStructure* data_structure,
//                              double degree_of_destruction = 0.25,
//                              int iterations = 100,
//                              double initial_temperature = 300.,
//                              double operator_decay_ratio = 0.9,
//                              const std::string& objective_path
//                              = "objective.csv",
//                              const std::string& opt_usage_path
//                              = "opt_usage.csv") {
//   using namespace tsp;
//   using namespace alns;

//   // 随机种子控制
//   RandomState rs{1};
//   // 构造State模型的初始解
//   State init_state = State::Init(data_structure, degree_of_destruction, rs);
//   // 实例化 适配于State的 退火跳版本的 alns
//   ALNS<State, Criterion::SimulatedAnnealing> alns{&rs};
//   // 添加State的几种邻域搜索算子
//   Operator<State> random_removal{State::RandomRemoval};
//   alns.add_destroy_operator(&random_removal, "D-Random");
//   Operator<State> greedy_insertion{State::GreedyInsertion};
//   alns.add_repair_operator(&greedy_insertion, "I-Greedy");
//   // 实例化 指数速率 退火跳接受机制
//   Criterion::SimulatedAnnealing
//     criterion(initial_temperature,
//               0,
//               0.999975,
//               Criterion::UPDATE_METHOD::exponential);
//   // 迭代计算
//   auto best = alns.iterate(init_state,
//                            {33., 9., 13., 1.}, // 4种邻域解状态对应的分数增量
//                            operator_decay_ratio,
//                            criterion,
//                            iterations,
//                            true,
//                            objective_path,
//                            opt_usage_path);
//   return best;
// }

// int main(int argc, char const* argv[]) {
//   tsp::DataStructure data("../../data/data.tsp");
//   data.Init();

//   auto state = run_alns_on_state(&data);
//   state.PrintResult();

//   return 0;
// }

/* Copyright 2026, Gurobi Optimization, LLC */

/*
   This example reads a model from a file, sets up a callback that
   monitors optimization progress and implements a custom
   termination strategy, and outputs progress information to the
   screen and to a log file.

   The termination strategy implemented in this callback stops the
   optimization of a MIP model once at least one of the following two
   conditions have been satisfied:
     1) The optimality gap is less than 10%
     2) At least 10000 nodes have been explored, and an integer feasible
        solution has been found.
   Note that termination is normally handled through Gurobi parameters
   (MIPGap, NodeLimit, etc.).  You should only use a callback for
   termination if the available parameters don't capture your desired
   termination criterion.
*/

#include "gurobi_c++.h"
#include <cmath>
#include <fstream>

using namespace std;

class mycallback : public GRBCallback {
public:
  double lastiter;
  double lastnode;
  int numvars;
  GRBVar* vars;
  ofstream* logfile;
  mycallback(int xnumvars, GRBVar* xvars, ofstream* xlogfile) {
    lastiter = lastnode = -GRB_INFINITY;
    numvars = xnumvars;
    vars = xvars;
    logfile = xlogfile;
  }

protected:
  void callback() {
    try {
      if (where == GRB_CB_POLLING) {
        // Ignore polling callback
      } else if (where == GRB_CB_PRESOLVE) {
        // Presolve callback
        int cdels = getIntInfo(GRB_CB_PRE_COLDEL);
        int rdels = getIntInfo(GRB_CB_PRE_ROWDEL);
        if (cdels || rdels) {
          cout << cdels << " columns and " << rdels << " rows are removed" << endl;
        }
      } else if (where == GRB_CB_SIMPLEX) {
        // Simplex callback
        double itcnt = getDoubleInfo(GRB_CB_SPX_ITRCNT);
        if (itcnt - lastiter >= 100) {
          lastiter = itcnt;
          double obj = getDoubleInfo(GRB_CB_SPX_OBJVAL);
          int ispert = getIntInfo(GRB_CB_SPX_ISPERT);
          double pinf = getDoubleInfo(GRB_CB_SPX_PRIMINF);
          double dinf = getDoubleInfo(GRB_CB_SPX_DUALINF);
          char ch;
          if (ispert == 0)
            ch = ' ';
          else if (ispert == 1)
            ch = 'S';
          else
            ch = 'P';
          cout << itcnt << " " << obj << ch << " " << pinf << " " << dinf << endl;
        }
      } else if (where == GRB_CB_MIP) {
        // General MIP callback
        double nodecnt = getDoubleInfo(GRB_CB_MIP_NODCNT);
        double objbst = getDoubleInfo(GRB_CB_MIP_OBJBST);
        double objbnd = getDoubleInfo(GRB_CB_MIP_OBJBND);
        int solcnt = getIntInfo(GRB_CB_MIP_SOLCNT);
        if (nodecnt - lastnode >= 100) {
          lastnode = nodecnt;
          int actnodes = (int)getDoubleInfo(GRB_CB_MIP_NODLFT);
          int itcnt = (int)getDoubleInfo(GRB_CB_MIP_ITRCNT);
          int cutcnt = getIntInfo(GRB_CB_MIP_CUTCNT);
          cout << nodecnt << " " << actnodes << " " << itcnt << " " << objbst << " " << objbnd
               << " " << solcnt << " " << cutcnt << endl;
        }
        if (fabs(objbst - objbnd) < 0.1 * (1.0 + fabs(objbst))) {
          cout << "Stop early - 10% gap achieved" << endl;
          abort();
        }
        if (nodecnt >= 10000 && solcnt) {
          cout << "Stop early - 10000 nodes explored" << endl;
          abort();
        }
      } else if (where == GRB_CB_MIPSOL) {
        // MIP solution callback
        int nodecnt = (int)getDoubleInfo(GRB_CB_MIPSOL_NODCNT);
        double obj = getDoubleInfo(GRB_CB_MIPSOL_OBJ);
        int solcnt = getIntInfo(GRB_CB_MIPSOL_SOLCNT);
        double* x = getSolution(vars, numvars);
        cout << "**** New solution at node " << nodecnt << ", obj " << obj << ", sol " << solcnt
             << ", x[0] = " << x[0] << " ****" << endl;
        delete[] x;
      } else if (where == GRB_CB_MIPNODE) {
        // MIP node callback
        cout << "**** New node ****" << endl;
        if (getIntInfo(GRB_CB_MIPNODE_STATUS) == GRB_OPTIMAL) {
          double* x = getNodeRel(vars, numvars);
          setSolution(vars, x, numvars);
          delete[] x;
        }
      } else if (where == GRB_CB_BARRIER) {
        // Barrier callback
        int itcnt = getIntInfo(GRB_CB_BARRIER_ITRCNT);
        double primobj = getDoubleInfo(GRB_CB_BARRIER_PRIMOBJ);
        double dualobj = getDoubleInfo(GRB_CB_BARRIER_DUALOBJ);
        double priminf = getDoubleInfo(GRB_CB_BARRIER_PRIMINF);
        double dualinf = getDoubleInfo(GRB_CB_BARRIER_DUALINF);
        double cmpl = getDoubleInfo(GRB_CB_BARRIER_COMPL);
        cout << itcnt << " " << primobj << " " << dualobj << " " << priminf << " " << dualinf << " "
             << cmpl << endl;
      } else if (where == GRB_CB_MESSAGE) {
        // Message callback
        string msg = getStringInfo(GRB_CB_MSG_STRING);
        *logfile << msg;
      }
    } catch (GRBException e) {
      cout << "Error number: " << e.getErrorCode() << endl;
      cout << e.getMessage() << endl;
    } catch (...) {
      cout << "Error during callback" << endl;
    }
  }
};

/* Copyright 2026, Gurobi Optimization, LLC */

/* Solve a traveling salesman problem on a randomly generated set of
   points using lazy constraints.   The base MIP model only includes
   'degree-2' constraints, requiring each node to have exactly
   two incident edges.  Solutions to this model may contain subtours -
   tours that don't visit every node.  The lazy constraint callback
   adds new constraints to cut them off. */

#include "gurobi_c++.h"
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <sstream>

using namespace std;

string itos(int i) {
  stringstream s;
  s << i;
  return s.str();
}
double distance(double* x, double* y, int i, int j);
void findsubtour(int n, double** sol, int* tourlenP, int* tour);

// Subtour elimination callback.  Whenever a feasible solution is found,
// find the smallest subtour, and add a subtour elimination constraint
// if the tour doesn't visit every node.

class subtourelim : public GRBCallback {
public:
  GRBVar** vars;
  int n;
  subtourelim(GRBVar** xvars, int xn) {
    vars = xvars;
    n = xn;
  }

protected:
  void callback() {
    try {
      if (where == GRB_CB_MIPSOL) {
        // Found an integer feasible solution - does it visit every node?
        double** x = new double*[n];
        int* tour = new int[n];
        int i, j, len;
        for (i = 0; i < n; i++)
          x[i] = getSolution(vars[i], n);

        findsubtour(n, x, &len, tour);

        if (len < n) {
          // Add subtour elimination constraint
          GRBLinExpr expr = 0;
          for (i = 0; i < len; i++)
            for (j = i + 1; j < len; j++)
              expr += vars[tour[i]][tour[j]];
          addLazy(expr <= len - 1);
        }

        for (i = 0; i < n; i++)
          delete[] x[i];
        delete[] x;
        delete[] tour;
      }
    } catch (GRBException e) {
      cout << "Error number: " << e.getErrorCode() << endl;
      cout << e.getMessage() << endl;
    } catch (...) {
      cout << "Error during callback" << endl;
    }
  }
};

// Given an integer-feasible solution 'sol', find the smallest
// sub-tour.  Result is returned in 'tour', and length is
// returned in 'tourlenP'.

void findsubtour(int n, double** sol, int* tourlenP, int* tour) {
  bool* seen = new bool[n];
  int bestind, bestlen;
  int i, node, len, start;

  for (i = 0; i < n; i++)
    seen[i] = false;

  start = 0;
  bestlen = n + 1;
  bestind = -1;
  node = 0;
  while (start < n) {
    for (node = 0; node < n; node++)
      if (!seen[node])
        break;
    if (node == n)
      break;
    for (len = 0; len < n; len++) {
      tour[start + len] = node;
      seen[node] = true;
      for (i = 0; i < n; i++) {
        if (sol[node][i] > 0.5 && !seen[i]) {
          node = i;
          break;
        }
      }
      if (i == n) {
        len++;
        if (len < bestlen) {
          bestlen = len;
          bestind = start;
        }
        start += len;
        break;
      }
    }
  }

  for (i = 0; i < bestlen; i++)
    tour[i] = tour[bestind + i];
  *tourlenP = bestlen;

  delete[] seen;
}

// Euclidean distance between points 'i' and 'j'.

double distance(double* x, double* y, int i, int j) {
  double dx = x[i] - x[j];
  double dy = y[i] - y[j];

  return sqrt(dx * dx + dy * dy);
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    cout << "Usage: tsp_c++ size" << endl;
    return 1;
  }

  int n = atoi(argv[1]);
  double* x = new double[n];
  double* y = new double[n];

  int i;
  for (i = 0; i < n; i++) {
    x[i] = ((double)rand()) / RAND_MAX;
    y[i] = ((double)rand()) / RAND_MAX;
  }

  GRBEnv* env = NULL;
  GRBVar** vars = NULL;

  vars = new GRBVar*[n];
  for (i = 0; i < n; i++)
    vars[i] = new GRBVar[n];

  try {
    int j;

    env = new GRBEnv();
    GRBModel model = GRBModel(*env);

    // Must set LazyConstraints parameter when using lazy constraints

    model.set(GRB_IntParam_LazyConstraints, 1);

    // Create binary decision variables

    for (i = 0; i < n; i++) {
      for (j = 0; j <= i; j++) {
        vars[i][j] = model.addVar(0.0,
                                  1.0,
                                  distance(x, y, i, j),
                                  GRB_BINARY,
                                  "x_" + itos(i) + "_" + itos(j));
        vars[j][i] = vars[i][j];
      }
    }

    // Degree-2 constraints

    for (i = 0; i < n; i++) {
      GRBLinExpr expr = 0;
      for (j = 0; j < n; j++)
        expr += vars[i][j];
      model.addConstr(expr == 2, "deg2_" + itos(i));
    }

    // Forbid edge from node back to itself

    for (i = 0; i < n; i++)
      vars[i][i].set(GRB_DoubleAttr_UB, 0);

    // Set callback function

    subtourelim cb = subtourelim(vars, n);
    model.setCallback(&cb);

    // Optimize model

    model.optimize();

    // Extract solution

    if (model.get(GRB_IntAttr_SolCount) > 0) {
      double** sol = new double*[n];
      for (i = 0; i < n; i++)
        sol[i] = model.get(GRB_DoubleAttr_X, vars[i], n);

      int* tour = new int[n];
      int len;

      findsubtour(n, sol, &len, tour);
      assert(len == n);

      cout << "Tour: ";
      for (i = 0; i < len; i++)
        cout << tour[i] << " ";
      cout << endl;

      for (i = 0; i < n; i++)
        delete[] sol[i];
      delete[] sol;
      delete[] tour;
    }

  } catch (GRBException e) {
    cout << "Error number: " << e.getErrorCode() << endl;
    cout << e.getMessage() << endl;
  } catch (...) {
    cout << "Error during optimization" << endl;
  }

  for (i = 0; i < n; i++)
    delete[] vars[i];
  delete[] vars;
  delete[] x;
  delete[] y;
  delete env;
  return 0;
}
