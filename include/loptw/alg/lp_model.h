///======================================================
/// Project :   loptw-alg
/// File    :   lp_model.h
///------------------------------------------------------
/// Time    :   2026/07/05 16:17:15
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#ifndef __LOPTW_ALG_INCLUDE_LOPTW_ALG_LP_MODEL_H__
#define __LOPTW_ALG_INCLUDE_LOPTW_ALG_LP_MODEL_H__

#include <memory>
#include <vector>

#include <loptw/instance/instance.h>

#include <gurobi_c++.h>

namespace loptw::alg {

class LPModel {
public:
  LPModel(std::shared_ptr<instance::Instance> inst,
          std::shared_ptr<std::vector<int>> p,
          std::shared_ptr<std::vector<int>> r,
          std::shared_ptr<std::vector<std::vector<int>>> z,
          std::shared_ptr<std::vector<std::vector<int>>> l,
          std::shared_ptr<std::vector<std::vector<int>>> m);

  ~LPModel() = default;

  int Optimize();

  double ObjValue();
  void GetSolution(std::vector<double>& xsol, std::vector<double>& ysol);

private:
  void AddObjective();
  void AddConstriants();
  void AddVariables();

private:
  std::shared_ptr<instance::Instance> inst;
  int T;
  int N;
  int F;

private:
  std::shared_ptr<GRBEnv> env;
  std::shared_ptr<GRBModel> model;

  // ---------- Variables ----------
  std::vector<GRBVar> x;              // x[N]
  std::vector<GRBVar> y;              // y[N]
  std::vector<std::vector<GRBVar>> d; // d[N][N]
  std::vector<std::vector<GRBVar>> a; // alpha[N][N]
  std::vector<std::vector<GRBVar>> b; // beta[N][N]

  // ---------- data ----------
  std::shared_ptr<std::vector<int>> p;
  std::shared_ptr<std::vector<int>> r;
  std::shared_ptr<std::vector<std::vector<int>>> z;
  std::shared_ptr<std::vector<std::vector<int>>> l;
  std::shared_ptr<std::vector<std::vector<int>>> m;

  int status_; // the status of the reoptimization model
};

} // namespace loptw::alg

#endif // __LOPTW_ALG_INCLUDE_LOPTW_ALG_LP_MODEL_H__
