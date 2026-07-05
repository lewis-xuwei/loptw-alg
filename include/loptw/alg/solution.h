///======================================================
/// Project :   loptw-alg
/// File    :   solution.h
///------------------------------------------------------
/// Time    :   2026/06/28 11:13:02
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#include <memory>

#include <loptw/alg/parameter.h>
#include <loptw/alg/sol_building.h>
#include <loptw/instance/instance.h>

namespace loptw::alg {

class Solution {
public:
  Solution(std::shared_ptr<instance::Instance> inst, std::shared_ptr<Parameter> parameter);
  ~Solution() = default;

  // Calculate the objective
  double Objective() const;

  // Print the result
  void PrintResult() const;

  bool operator<(const Solution& solution) const;

  std::shared_ptr<Solution> Copy();

private:
  std::shared_ptr<instance::Instance> inst_;
  std::shared_ptr<Parameter> parameter_;

  std::vector<SolBuilding> buildings_;   // solution for each building
  std::vector<int> unserved_task_nodes_; // unserved task nodes

  //------------ shared memory for all buildings ------------
  std::vector<std::vector<int>> left_; // left[i][j] = 1 => i is in the left of j
  std::vector<std::vector<int>> top_;  // top[i][j] = 1 => i is in the top of j

  double obj_;
};

} // namespace loptw::alg
