#include <iostream>
#include <memory>

#include <fmt/core.h>
#include <fmt/ranges.h>

#include <loptw/grb/grb_solver.h>
#include <loptw/instance/instance.h>

using namespace std;

int main(int argc, char *argv[]) {
  auto instance = loptw::instance::Instance::FromPath("../../data/test1.json");
  auto grb_solver = loptw::grb::GRBSolver(instance);
  grb_solver.AddVariables();
  grb_solver.AddObjective();
  grb_solver.AddConstraints();
  grb_solver.Optimize();
  return 0;
}
