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
  std::vector<loptw::alg::Skyline> skylines = {{0, 3, 3}, {3, 5, 1}, {5, 10, 2}};
  loptw::alg::Skylines::MergeSkyline(skylines, 0.0, 10);

  for (const auto& skyline : skylines) {
    fmt::println("Skyline: [{}, {}, {}]", skyline.left, skyline.right, skyline.height);
  }

  loptw::alg::Skylines::MergeSkyline(skylines, 0.0, 10);

  for (const auto& skyline : skylines) {
    fmt::println("Skyline: [{}, {}, {}]", skyline.left, skyline.right, skyline.height);
  }

  bool located;
  located = loptw::alg::Skylines::Locate(skylines, 5.0, 2.0, 5, 0);
  fmt::println("Location found: {}", located); // Expected: true

  located = loptw::alg::Skylines::Locate(skylines, 5.0, 2.01, 5, 0);
  fmt::println("Location found: {}", located); // Expected: false

  located = loptw::alg::Skylines::Locate(skylines, 5.0, 2.0, 5, 1);
  fmt::println("Location found: {}", located); // Expected: false
  located = loptw::alg::Skylines::Locate(skylines, 2.0, 4.0, 5, 1);
  fmt::println("Location found: {}", located); // Expected: false

  located = loptw::alg::Skylines::Locate(skylines, 5.0, 2.0, 5, 2);
  fmt::println("Location found: {}", located); // Expected: true

  return 0;
}
