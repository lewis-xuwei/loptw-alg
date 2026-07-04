///======================================================
/// Project :   loptw-alg
/// File    :   state_initialization.cpp
///------------------------------------------------------
/// Time    :   2026/07/04 18:52:05
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#include <loptw/alg/state.h>

namespace loptw::alg {

State State::Initialization(std::shared_ptr<instance::Instance> inst,
                            std::shared_ptr<Parameter> param) {
  int N = inst->GetNumTaskNodes();
  int T = inst->GetNumBuildings();

  State state{};
  state.buildings_.reserve(T);
  state.unserved_task_nodes_.reserve(N);
  for (int i = 0; i < N; ++i) {
    state.unserved_task_nodes_.push_back(i);
  }
  state.left_ = std::vector<std::vector<int>>(N, std::vector<int>(N, 0));
  state.top_ = std::vector<std::vector<int>>(N, std::vector<int>(N, 0));

  return state;
}

} // namespace loptw::alg