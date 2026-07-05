///======================================================
/// Project :   loptw-alg
/// File    :   solution_initialization.cpp
///------------------------------------------------------
/// Time    :   2026/07/04 18:52:05
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#include <loptw/alg/solution.h>

namespace loptw::alg {

Solution Solution::Initialization(std::shared_ptr<instance::Instance> inst,
                                  std::shared_ptr<Parameter> param) {
  int N = inst->GetNumTaskNodes();
  int T = inst->GetNumBuildings();

  Solution sol{};
  sol.buildings_.reserve(T);
  sol.unserved_task_nodes_.reserve(N);
  for (int i = 0; i < N; ++i) {
    sol.unserved_task_nodes_.push_back(i);
  }
  sol.left_ = std::vector<std::vector<int>>(N, std::vector<int>(N, 0));
  sol.top_ = std::vector<std::vector<int>>(N, std::vector<int>(N, 0));

  return sol;
}

} // namespace loptw::alg