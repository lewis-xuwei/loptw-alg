///======================================================
/// Project :   loptw-bnc
/// File    :   instance.cpp
///------------------------------------------------------
/// Time    :   2026/04/25 10:54:11
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#include <fstream>

#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

#include <loptw/instance/instance.h>

namespace loptw::instance {

Instance::Instance() : buildings_{}, tasknodes_{}, workflows_{} {}

void Instance::set_instance_path(const std::string path) {
  instance_path_ = path;
}

const std::string &Instance::instance_path() const { return instance_path_; }

const Instance::Pool<Building> &Instance::buildings() const {
  return buildings_;
}
const Instance::Pool<TaskNode> &Instance::tasknodes() const {
  return tasknodes_;
}
const Instance::Pool<Workflow> &Instance::workflows() const {
  return workflows_;
}

std::shared_ptr<Instance> Instance::FromPath(const std::string path) {
  using namespace nlohmann;

  // Read data from a instance file
  std::ifstream instance_file(path);
  if (!instance_file) {
    spdlog::error("Instance file: {} cannot be opened!", path);
  }
  spdlog::info("Instance file: {} has been opened!", path);

  json instance_json = json::parse(instance_file);

  auto instance = std::make_shared<Instance>();
  instance->set_instance_path(path);

  for (auto building_json : instance_json["buildings"]) {
    auto building = std::make_shared<Building>(
        building_json["id"], building_json["x"], building_json["y"],
        building_json["w"], building_json["h"], building_json["c"]);

    if (nullptr != building)
      instance->AddBuilding(building);
  }
  spdlog::info("Add {} buildings", instance->GetNumBuildings());

  for (auto tasknode_json : instance_json["task_nodes"]) {
    auto tasknode = std::make_shared<TaskNode>(
        tasknode_json["id"], tasknode_json["w"], tasknode_json["h"]);

    if (nullptr != tasknode)
      instance->AddTaskNode(tasknode);
  }
  spdlog::info("Add {} tasknodes", instance->GetNumTaskNodes());

  for (auto workflow_json : instance_json["workflow"]) {
    auto workflow = std::make_shared<Workflow>(workflow_json["source"],
                                               workflow_json["target"],
                                               workflow_json["quantity"]);
    if (nullptr != workflow)
      instance->AddWorkflow(workflow);
  }
  spdlog::info("Add {} workflows", instance->GetNumWorkflows());

  return instance;
}

size_t Instance::GetNumBuildings() const { return buildings_.size(); }

size_t Instance::GetNumTaskNodes() const { return tasknodes_.size(); }

size_t Instance::GetNumWorkflows() const { return workflows_.size(); }

bool Instance::Validate() const {
  // 1. any building do not overlap with each other
  for (auto [building_id1, building1] : buildings_) {
    for (auto [building_id2, building2] : buildings_) {
      if (building_id1 == building_id2)
        continue;
      if (building1->OverlapWith(*building2))
        return false;
    }
  }

  // 2. workflow is valid that the source and target of workflow exist
  for (auto [_, workflow] : workflows_) {
    if (tasknodes_.find(workflow->source_) == tasknodes_.end())
      return false;
    if (tasknodes_.find(workflow->target_) == tasknodes_.end())
      return false;
  }

  return true;
}

bool Instance::AddBuilding(const std::shared_ptr<Building> building,
                           bool overwrite) {
  auto iter = buildings_.find(building->building_id_);
  if (iter != buildings_.end() && overwrite == false) {
    spdlog::debug("building {} existed", building->building_id_);
    return true;
  }

  buildings_.insert({building->building_id_, building});

  return true;
}

bool Instance::RemoveBuilding(const Index building_id) {
  auto iter = buildings_.find(building_id);
  if (iter == buildings_.end()) {
    spdlog::debug("building {} not found", building_id);
    return true;
  }

  buildings_.erase(building_id);
  return true;
}

bool Instance::AddTaskNode(const std::shared_ptr<TaskNode> tasknode,
                           bool overwrite) {
  auto iter = tasknodes_.find(tasknode->tasknode_id_);
  if (iter != tasknodes_.end() && overwrite == false) {
    spdlog::debug("tasknode {} existed", tasknode->tasknode_id_);
    return true;
  }

  tasknodes_.insert({tasknode->tasknode_id_, tasknode});
  return true;
}

bool Instance::RemoveTaskNode(const Index tasknode_id) {
  auto iter = tasknodes_.find(tasknode_id);
  if (iter == tasknodes_.end()) {
    spdlog::debug("tasknode_id {} not found", tasknode_id);
    return true;
  }

  tasknodes_.erase(tasknode_id);
  return true;
}

bool Instance::AddWorkflow(const std::shared_ptr<Workflow> workflow,
                           bool overwrite) {

  auto iter = workflows_.find({workflow->source_, workflow->target_});
  if ((iter != workflows_.end()) && overwrite == false) {
    spdlog::debug("workflow [{}->{}] existed", workflow->source_,
                  workflow->target_);
    return true;
  }

  workflows_.insert({{workflow->source_, workflow->target_}, workflow});
  return true;
}

bool Instance::RemoveWorkflow(Index source, Index target) {
  auto iter = workflows_.find({source, target});
  if (iter == workflows_.end()) {
    spdlog::debug("workflow [{}->{}] not found", source, target);
    return true;
  }

  workflows_.erase({source, target});
  return true;
}

} // namespace loptw::instance
