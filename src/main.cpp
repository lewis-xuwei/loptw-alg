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

#include <alns/ALNS.hpp>
#include <tsp/DataStructure.h>
#include <tsp/Point.h>
#include <tsp/State.h>

// 导出为动态库或者直接在main函数跑
tsp::State run_alns_on_state(tsp::DataStructure* data_structure,
                             double degree_of_destruction = 0.25,
                             int iterations = 100,
                             double initial_temperature = 300.,
                             double operator_decay_ratio = 0.9,
                             const std::string& objective_path
                             = "objective.csv",
                             const std::string& opt_usage_path
                             = "opt_usage.csv") {
  using namespace tsp;
  using namespace alns;

  // 构造State模型的初始解
  State init_state = State::Init(data_structure, degree_of_destruction);
  // 随机种子控制
  RandomState rs{1};
  // 实例化 适配于State的 退火跳版本的 alns
  ALNS<State, Criterion::SimulatedAnnealing> alns{&rs};
  // 添加State的几种邻域搜索算子
  Operator<State> random_removal{State::RandomRemoval};
  alns.add_destroy_operator(&random_removal, "D-Random");
  Operator<State> greedy_insertion{State::GreedyInsertion};
  alns.add_repair_operator(&greedy_insertion, "I-Greedy");
  // 实例化 指数速率 退火跳接受机制
  Criterion::SimulatedAnnealing
    criterion(initial_temperature,
              0,
              0.999975,
              Criterion::UPDATE_METHOD::exponential);
  // 迭代计算
  auto best = alns.iterate(init_state,
                           {33., 9., 13., 1.}, // 4种邻域解状态对应的分数增量
                           operator_decay_ratio,
                           criterion,
                           iterations,
                           true,
                           objective_path,
                           opt_usage_path);
  return best;
}

int main(int argc, char const* argv[]) {
  tsp::DataStructure data("../../data/data.tsp");
  data.Init();

  auto state = run_alns_on_state(&data);
  state.PrintResult();

  return 0;
}
