///======================================================
/// Project :   loptw-bnc
/// File    :   test_random.cpp
///------------------------------------------------------
/// Time    :   2026/05/20 14:53:08
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#include <memory>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <loptw/utility/random.h>

TEST_CASE("Test Class `loptw::utility::Random'") {
  using namespace loptw::utility;

  Random::SetSeed(42);
  for (int i = 0; i < 10; ++i) {
    REQUIRE(Random::Uniform(0.0, 1.0) >= 0.0);
    REQUIRE(Random::Uniform(0.0, 1.0) < 1.0);
    REQUIRE(Random::Uniform(1, 10) >= 1);
    REQUIRE(Random::Uniform(1, 10) <= 10);
    REQUIRE(Random::Index(5) >= 0);
    REQUIRE(Random::Index(5) < 5);
  }
}
