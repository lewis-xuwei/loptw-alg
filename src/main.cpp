#include <iomanip>
#include <iostream>
#include <memory>

#include <fmt/core.h>
#include <fmt/ranges.h>

#include <loptw/alg/solution.h>
#include <loptw/alg/tabusearch.h>
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
  auto instance = loptw::instance::Instance::FromPath("../../data/test1.json");
  auto tabusearch = loptw::alg::TabuSearch(instance, nullptr);
  auto sol = tabusearch.Initialization();
  return 0;
}
