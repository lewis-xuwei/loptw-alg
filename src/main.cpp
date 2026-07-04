#include <iomanip>
#include <iostream>
#include <memory>

#include <fmt/core.h>
#include <fmt/ranges.h>

#include <loptw/alg/state.h>
#include <loptw/grb/grb_solver.h>
#include <loptw/instance/instance.h>

using namespace std;

void GurobiOptimize() {
  auto instance = loptw::instance::Instance::FromPath("../../data/test1.json");
  auto grb_solver = loptw::grb::GRBSolver(instance);
  grb_solver.AddVariables();
  grb_solver.AddObjective();
  grb_solver.AddConstraints();
  grb_solver.Optimize();
  // grb_solver.OptimizeWithCoverInequalityCallback();
}

int main(int argc, char* argv[]) {
  using namespace loptw::instance;

  auto instance = Instance::FromPath("../../data/test1.json");
  auto param = std::make_shared<loptw::alg::Parameter>();
  loptw::alg::State state = loptw::alg::State::Initialization(instance, param);
  return 0;
}
