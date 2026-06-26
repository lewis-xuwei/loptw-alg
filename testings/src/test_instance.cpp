///======================================================
/// Project :   loptw-bnc
/// File    :   test_instance.cpp
///------------------------------------------------------
/// Time    :   2026/05/09 12:35:54
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#include <memory>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <loptw/instance/instance.h>

using namespace loptw;
using loptw::instance::Index;

TEST_CASE("Test Class `loptw::instance::Instance'") {
  SUBCASE("set_instance_path") {
    auto instance = std::make_shared<instance::Instance>();
    REQUIRE(instance->instance_path().size() == 0);

    instance->set_instance_path("a/b/c");
    REQUIRE_EQ(instance->instance_path(), "a/b/c");
  }

  SUBCASE("AddBuilding and RemoveBuilding") {
    auto instance = std::make_shared<instance::Instance>();
    auto building1 = std::make_shared<instance::Building>(1, 2, 3, 4, 5, 6);
    auto building2 = std::make_shared<instance::Building>(2, 3, 4, 5, 6, 7);

    instance->AddBuilding(building1);
    REQUIRE(instance->GetNumBuildings() == 1);
    instance->AddBuilding(building1);
    REQUIRE(instance->GetNumBuildings() == 1);
    instance->AddBuilding(building2);
    REQUIRE(instance->GetNumBuildings() == 2);
    instance->RemoveBuilding(Index(1));
    REQUIRE(instance->GetNumBuildings() == 1);
    instance->RemoveBuilding(Index(1));
    REQUIRE(instance->GetNumBuildings() == 1);
    instance->RemoveBuilding(Index(2));
    REQUIRE(instance->GetNumBuildings() == 0);
    instance->RemoveBuilding(Index(2));
    REQUIRE(instance->GetNumBuildings() == 0);
  }

  SUBCASE("AddTaskNode and RemoveTaskNode") {
    auto instance = std::make_shared<instance::Instance>();
    auto tasknode1 = std::make_shared<instance::TaskNode>(1, 4, 7);
    auto tasknode2 = std::make_shared<instance::TaskNode>(2, 5, 8);
    instance->AddTaskNode(tasknode1);
    REQUIRE(instance->GetNumTaskNodes() == 1);
    instance->AddTaskNode(tasknode1);
    REQUIRE(instance->GetNumTaskNodes() == 1);
    instance->AddTaskNode(tasknode2);
    REQUIRE(instance->GetNumTaskNodes() == 2);

    instance->RemoveTaskNode(Index(1));
    REQUIRE(instance->GetNumTaskNodes() == 1);
    instance->RemoveTaskNode(Index(1));
    REQUIRE(instance->GetNumTaskNodes() == 1);
    instance->RemoveTaskNode(Index(2));
    REQUIRE(instance->GetNumTaskNodes() == 0);
    instance->RemoveTaskNode(Index(2));
    REQUIRE(instance->GetNumTaskNodes() == 0);
  }

  SUBCASE("AddWorkflow and RemoveWorkflow") {
    auto instance = std::make_shared<instance::Instance>();
    auto workflow12 = std::make_shared<instance::Workflow>(1, 2, 3);
    auto workflow21 = std::make_shared<instance::Workflow>(2, 1, 3);

    instance->AddWorkflow(workflow12);
    REQUIRE(instance->GetNumWorkflows() == 1);
    instance->AddWorkflow(workflow12);
    REQUIRE(instance->GetNumWorkflows() == 1);
    instance->AddWorkflow(workflow21);
    REQUIRE(instance->GetNumWorkflows() == 2);

    instance->RemoveWorkflow(Index(1), Index(2));
    REQUIRE(instance->GetNumWorkflows() == 1);
    instance->RemoveWorkflow(Index(1), Index(2));
    REQUIRE(instance->GetNumWorkflows() == 1);
    instance->RemoveWorkflow(Index(2), Index(1));
    REQUIRE(instance->GetNumWorkflows() == 0);
    instance->RemoveWorkflow(Index(2), Index(1));
    REQUIRE(instance->GetNumWorkflows() == 0);
  }

  SUBCASE("FromPath-loptw.json") {
    auto instance = instance::Instance::FromPath(LOPTW_DATA_DIR "/loptw.json");
    // REQUIRE_EQ(instance->instance_path(), "../data/loptw.json");
    REQUIRE(instance->GetNumBuildings() == 10);
    REQUIRE(instance->GetNumTaskNodes() == 20);
    REQUIRE(instance->GetNumWorkflows() == 27);
    REQUIRE(instance->Validate() == true);
  }
}