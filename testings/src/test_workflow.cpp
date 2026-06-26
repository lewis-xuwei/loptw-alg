///======================================================
/// Project :   loptw-bnc
/// File    :   test_workflow.cpp
///------------------------------------------------------
/// Time    :   2026/05/09 12:36:27
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#include <memory>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <loptw/instance/workflow.h>

using namespace loptw;

TEST_CASE("Test Class `loptw::instance::Workflow'") {

  auto workflow = std::make_shared<instance::Workflow>(1, 2, 3);

  REQUIRE_EQ(1, workflow->source_);
  REQUIRE_EQ(2, workflow->target_);
  REQUIRE_GE(1E6, abs(workflow->quantity_ - 3.0));
}