///======================================================
/// Project :   loptw-alg
/// File    :   solution.h
///------------------------------------------------------
/// Time    :   2026/06/28 11:13:02
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#ifndef __LOPTW_ALG_INCLUDE_LOPTW_ALG_SOLUTION_H__
#define __LOPTW_ALG_INCLUDE_LOPTW_ALG_SOLUTION_H__

#include <memory>

#include <loptw/alg/parameter.h>
#include <loptw/alg/sol_building.h>
#include <loptw/instance/instance.h>

namespace loptw::alg {

class Solution {
  friend class TabuSearch;

public:
  Solution(std::shared_ptr<instance::Instance> inst, std::shared_ptr<Parameter> parameter);
  ~Solution() = default;

  // Calculate the objective
  double Objective() const;

  // Print the result
  void PrintResult() const;

  bool operator<(const Solution& solution) const;

  std::shared_ptr<Solution> Copy();
  bool IsFeasible(); // each task node is served and lp problem is optimal
  void Decode();     // analyze l,m,z,p,r
  void Reoptimization();

private:
  std::shared_ptr<instance::Instance> inst_;
  int T;
  int N;
  int F;

  std::shared_ptr<Parameter> parameter_;

  std::vector<SolBuilding> buildings_;   // solution for each building
  std::vector<int> unserved_task_nodes_; // unserved task nodes

  //------------ shared memory for all buildings ------------
  std::vector<std::vector<int>> left_; // left[i][j] = 1 => i is in the left of j
  std::vector<std::vector<int>> top_;  // top[i][j] = 1 => i is in the top of j

  std::vector<std::vector<int>> z_; // z[i][t] =1 => i is located in building t
  std::vector<int> p_;              // p[t] = 1 => building t is used
  std::vector<int> r_;              // r[i] = 1 => task node is rotated when placed
  std::vector<double> x_;           // x coordination
  std::vector<double> y_;           // y coordination

  double obj_; // obtain from lp problem
  int status_; // 0: lp optimal; otherwise, infeasible
};

} // namespace loptw::alg

#endif // __LOPTW_ALG_INCLUDE_LOPTW_ALG_SOLUTION_H__
