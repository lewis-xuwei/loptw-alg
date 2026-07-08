///======================================================
/// Project :   loptw-alg
/// File    :   tabusearch.cpp
///------------------------------------------------------
/// Time    :   2026/07/08 20:07:40
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#include <loptw/alg/tabusearch.h>
#include <loptw/utility/random.h>

namespace loptw::alg {

TabuSearch::TabuSearch(std::shared_ptr<instance::Instance> inst, std::shared_ptr<Parameter> para) :
  inst_{inst}, para_{para}, timer_{} {
  T = inst->GetNumBuildings();
  N = inst->GetNumTaskNodes();
  F = inst->GetNumWorkflows();

  tabu_list_ = std::make_shared<TabuList>(N, 10);
}

// 解的初始化
std::shared_ptr<Solution> TabuSearch::Initialization() {
  using namespace loptw::utility;

  std::vector<int> task_list = Random::RandomPermutation(N);
  std::vector<int> place(N, 0);
  std::vector<bool> rotated(N, false);
  for (int i = 0; i < N; i++) {
    place[i] = Random::Index(T);
    rotated[i] = static_cast<bool>(Random::Index(2));
  }

  auto solution = std::make_shared<Solution>(inst_, para_);
  solution->buildings_ = std::vector<SolBuilding>();
  for (int t = 0; t < T; ++t) {
    std::vector<int> task_list_t = std::vector<int>();
    std::vector<bool> rotated_t = std::vector<bool>();
    for (int i = 0; i < N; i++) {
      int taskid = task_list[i];
      bool rotation = rotated[i];
      if (place[i] == t) {
        task_list_t.push_back(taskid);
        rotated_t.push_back(rotation);
      }
    }
    solution->buildings_.push_back(SolBuilding(inst_, t, task_list_t, rotated_t));
  }

  solution->Reoptimization();

  return solution;
}

// 迭代过程
void TabuSearch::Run() {}

} // namespace loptw::alg
