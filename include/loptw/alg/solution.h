///======================================================
/// Project :   loptw-alg
/// File    :   solution.h
///------------------------------------------------------
/// Time    :   2026/06/28 11:13:02
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#include <alns/RandomState.h>
#include <loptw/alg/parameter.h>
#include <loptw/alg/sol_building.h>

namespace loptw::alg {

class Solution {
public:
  // Calculate the objective
  double Objective() const;

  // Print the result
  void PrintResult() const;

  // Initial solution for loptw
  static Solution Initialization(std::shared_ptr<instance::Instance> inst,
                                 std::shared_ptr<Parameter> param);

  static Solution RandomRemoval(const Solution& state, alns::RandomState& rnd_state);
  static Solution RandomRepair(const Solution& state, alns::RandomState& rnd_state);
  static Solution BestRepair(const Solution& state, alns::RandomState& rnd_state);

private:
  std::vector<SolBuilding> buildings_;   // solution for each building
  std::vector<int> unserved_task_nodes_; // unserved task nodes

  //------------ shared memory for all buildings ------------
  std::vector<std::vector<int>> left_; // left[i][j] = 1 => i is in the left of j
  std::vector<std::vector<int>> top_;  // top[i][j] = 1 => i is in the top of j
};

} // namespace loptw::alg
