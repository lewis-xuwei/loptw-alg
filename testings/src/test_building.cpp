///======================================================
/// Project :   loptw-bnc
/// File    :   test_building.cpp
///------------------------------------------------------
/// Time    :   2026/05/09 12:35:43
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#include <memory>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <loptw/instance/building.h>

TEST_CASE("Test Class `loptw::instance::Building'") {
  SUBCASE("Basic of building") {
    using namespace std;
    using loptw::instance::Building;
    auto building = make_shared<Building>(1, 2, 3, 4, 5, 6.0);

    REQUIRE_EQ(1, building->building_id_);
    REQUIRE_GE(1E6, abs(building->left_coord_ - 2));
    REQUIRE_GE(1E6, abs(building->bottom_coord_ - 3));
    REQUIRE_GE(1E6, abs(building->width_ - 4));
    REQUIRE_GE(1E6, abs(building->length_ - 5));
    REQUIRE_GE(1E6, abs(building->rent_cost_ - 6.0));
    REQUIRE_GE(1E6, abs(building->right_coord_ - 6.0));
    REQUIRE_GE(1E6, abs(building->top_coord_ - 8.0));
  }
  SUBCASE("Overlapping test of building") {
    using namespace std;
    using loptw::instance::Building;

    auto building1 = make_shared<Building>(1, 1, 1, 2, 2, 6.0);
    auto building2 = make_shared<Building>(1, 2, 2, 2, 2, 6.0);

    auto building3 = make_shared<Building>(1, 0, 1, 0.5, 2, 6.0);
    auto building4 = make_shared<Building>(1, 1, 0, 2, 0.5, 6.0);
    auto building5 = make_shared<Building>(1, 3.0001, 1, 2, 2, 6.0);
    auto building6 = make_shared<Building>(1, 1, 3.0001, 2, 2, 6.0);

    // 1 overlap with 2: true
    REQUIRE_EQ(building1->OverlapWith(*building2), true);

    // 3 is in the leftside of 1
    REQUIRE_EQ(building1->OverlapWith(*building3), false);
    // 4 is in the below of 1
    REQUIRE_EQ(building1->OverlapWith(*building4), false);
    // 5 is in the rightside of 1
    REQUIRE_EQ(building1->OverlapWith(*building5), false);
    // 6 is in the top of 1
    REQUIRE_EQ(building1->OverlapWith(*building6), false);
  }
}