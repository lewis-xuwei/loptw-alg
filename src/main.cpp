#include <iomanip>
#include <iostream>
#include <memory>

#include <fmt/core.h>
#include <fmt/ranges.h>

#include <loptw/alg/skyline.h>
#include <loptw/grb/grb_solver.h>
#include <loptw/instance/instance.h>

using namespace std;

int main(int argc, char* argv[]) {
  std::vector<loptw::alg::Skyline> buildings = {{0, 3, 3}, {3, 5, 1}, {5, 8, 2}};
  auto skyline = loptw::alg::Skylines::Merge(buildings);

  fmt::println("Merged Skyline: {}", skyline);

  bool located;
  located = loptw::alg::Skylines::Locate(buildings, 5.0, 2.0, 5, 0);
  fmt::println("Location found: {}", located);

  located = loptw::alg::Skylines::Locate(buildings, 5.0, 2.0, 5, 1);
  fmt::println("Location found: {}", located);

  located = loptw::alg::Skylines::Locate(buildings, 5.0, 2.0, 5, 2);
  fmt::println("Location found: {}", located);

  return 0;
}
