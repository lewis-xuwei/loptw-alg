///======================================================
/// Project :   loptw-bnc
/// File    :   test_tasknode.cpp
///------------------------------------------------------
/// Time    :   2026/05/09 12:36:17
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#include <memory>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <loptw/instance/tasknode.h>

using namespace loptw;

TEST_CASE("Test Class `loptw::instance::TaskNode'") {

  auto tasknode = std::make_shared<instance::TaskNode>(1, 2, 3);

  REQUIRE_EQ(1, tasknode->tasknode_id_);
  REQUIRE_GE(1E6, abs(tasknode->width_ - 2));
  REQUIRE_GE(1E6, abs(tasknode->length_ - 3));
}