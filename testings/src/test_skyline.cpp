///======================================================
/// Project :   loptw-alg
/// File    :   test_skyline.cpp
///------------------------------------------------------
/// Time    :   2026/07/02 17:11:17
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#include <memory>
#include <thread>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <loptw/alg/skyline.h>

TEST_CASE("Test Class `loptw::alg::Skyline'") {
  using namespace loptw::alg;
  SUBCASE("skyline-1") {
    std::vector<std::vector<double>> buildings = {{5.0, 12.0, 12.0},
                                                  {3.0, 7.0, 15.0},
                                                  {15.0, 20.0, 10.0},
                                                  {2.0, 9.0, 10.0},
                                                  {19.0, 24.0, 8.0}};
    auto skyline = Skyline::GetSkyline(buildings);
    std::vector<std::vector<double>> expected = {{2.0, 10.0},
                                                 {3.0, 15.0},
                                                 {7.0, 12.0},
                                                 {12.0, 0.0},
                                                 {15.0, 10.0},
                                                 {20.0, 8.0},
                                                 {24.0, 0.0}};
    REQUIRE(skyline.size() == 7);
    for (const auto& point : skyline) {
      REQUIRE(std::find(expected.begin(), expected.end(), point) != expected.end());
    }
  }

  SUBCASE("skyline-1") {
    std::vector<std::vector<double>> buildings
      = {{0, 1, 3.0}, {1, 2, 1}, {1, 2, 3.01}, {2, 3, 2}, {2, 3, 0}};
    auto skyline = Skyline::GetSkyline(buildings);
    std::vector<std::vector<double>> expected = {{0.0, 3.0}, {1.0, 3.01}, {2.0, 2.0}, {3.0, 0.0}};
    REQUIRE(skyline.size() == 4);
    for (const auto& point : skyline) {
      REQUIRE(std::find(expected.begin(), expected.end(), point) != expected.end());
    }
  }
}