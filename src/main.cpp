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
  std::vector<loptw::alg::Skyline> buildings = {{5.0, 12.0, 12.0},
                                                {3.0, 7.0, 15.0},
                                                {15.0, 20.0, 10.0},
                                                {2.0, 9.0, 10.0},
                                                {19.0, 24.0, 8.0}};
  auto skyline = loptw::alg::SkylineMerger::Merge(buildings);

  fmt::println("Merged Skyline: {}", skyline);

  return 0;
}
