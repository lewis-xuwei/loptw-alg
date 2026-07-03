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
  std::vector<loptw::alg::Skyline> skylines = {{5.0, 12.0, 12.0},
                                               {3.0, 7.0, 15.0},
                                               {15.0, 20.0, 10.0},
                                               {2.0, 9.0, 10.0},
                                               {19.0, 24.0, 8.0}};
  loptw::alg::Skylines::MergeSkyline(skylines, 0.0, 25.0);

  for (const auto& skyline : skylines) {
    fmt::println("Skyline: [{}, {}, {}]", skyline.left, skyline.right, skyline.height);
  }

  loptw::alg::Skylines::MergeSkyline(skylines, 0.0, 25.0);

  for (const auto& skyline : skylines) {
    fmt::println("Skyline: [{}, {}, {}]", skyline.left, skyline.right, skyline.height);
  }

  bool located;
  located = loptw::alg::Skylines::Locate(skylines, 5.0, 2.0, 5, 0);
  fmt::println("Location found: {}", located);

  located = loptw::alg::Skylines::Locate(skylines, 5.0, 2.0, 5, 1);
  fmt::println("Location found: {}", located);

  located = loptw::alg::Skylines::Locate(skylines, 5.0, 2.0, 5, 2);
  fmt::println("Location found: {}", located);

  return 0;
}
