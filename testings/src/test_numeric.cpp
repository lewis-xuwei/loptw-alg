///======================================================
/// Project :   loptw-bnc
/// File    :   test_numeric.cpp
///------------------------------------------------------
/// Time    :   2026/05/20 14:53:08
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#include <memory>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <loptw/utility/numeric.h>

TEST_CASE("Test Class `loptw::utility::Numeric'") {
  using namespace loptw::utility;

  REQUIRE(Numeric::Equal(1.1, 1.000000000, 1e-4) == false);
  REQUIRE(Numeric::Equal(1.01, 1.000000000, 1e-4) == false);
  REQUIRE(Numeric::Equal(1.001, 1.000000000, 1e-4) == false);
  REQUIRE(Numeric::Equal(1.0001, 1.000000000, 1e-4) == true);

  REQUIRE(Numeric::Equal(1.0000001, 1.000000000) == false);
  REQUIRE(Numeric::Equal(1.00000001, 1.000000000) == false);
  REQUIRE(Numeric::Equal(1.000000001, 1.000000000) == false);
  REQUIRE(Numeric::Equal(1.0000000001, 1.000000000) == true);
  REQUIRE(Numeric::Equal(1.00000000001, 1.000000000) == true);
  REQUIRE(Numeric::Equal(1.000000000001, 1.000000000) == true);

  REQUIRE(Numeric::EqualSlightGreater(1.0000001, 1.000000000) == false);
  REQUIRE(Numeric::EqualSlightGreater(1.00000001, 1.000000000) == false);
  REQUIRE(Numeric::EqualSlightGreater(1.000000001, 1.000000000) == false);
  REQUIRE(Numeric::EqualSlightGreater(1.0000000001, 1.000000000) == true);
  REQUIRE(Numeric::EqualSlightGreater(1.00000000001, 1.000000000) == true);
  REQUIRE(Numeric::EqualSlightGreater(1.000000000001, 1.000000000) == true);

  REQUIRE(Numeric::EqualSlightLess(0.9999999, 1.000000000) == false);
  REQUIRE(Numeric::EqualSlightLess(0.99999999, 1.000000000) == false);
  REQUIRE(Numeric::EqualSlightLess(0.999999999, 1.000000000) == true);
  REQUIRE(Numeric::EqualSlightLess(0.9999999999, 1.000000000) == true);
  REQUIRE(Numeric::EqualSlightLess(0.99999999999, 1.000000000) == true);
  REQUIRE(Numeric::EqualSlightLess(0.999999999999, 1.000000000) == true);

  REQUIRE(Numeric::IsIntegral(0.9999999) == false);
  REQUIRE(Numeric::IsIntegral(0.99999999) == false);
  REQUIRE(Numeric::IsIntegral(0.999999999) == true);
  REQUIRE(Numeric::IsIntegral(0.9999999999) == true);
  REQUIRE(Numeric::IsIntegral(0.99999999999) == true);
  REQUIRE(Numeric::IsIntegral(0.999999999999) == true);

  REQUIRE(Numeric::IndexOfMostFractional({0.1, 0.2, 0.3, 0.4, 0.7},
                                         {0, 1, 2, 3, 4}) == 3);
  REQUIRE(Numeric::IndexOfMostFractional({-1.1, -0.2, -0.3, -7.4, -0.7},
                                         {0, 1, 2, 3, 4}) == 3);
  REQUIRE(Numeric::IndexOfMostFractional({0.1, 0.2, 0.3, 0.4, 0.5, 0.6},
                                         {0, 1, 2, 3, 4, 5}) == 4);
  REQUIRE(Numeric::IndexOfMostFractional({}, {}) == -1);
}