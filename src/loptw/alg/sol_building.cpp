///======================================================
/// Project :   loptw-alg
/// File    :   sol_building.cpp
///------------------------------------------------------
/// Time    :   2026/06/29 15:22:09
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#include <loptw/alg/sol_building.h>

namespace loptw::alg {

SolBuilding::SolBuilding(std::shared_ptr<instance::Instance> inst,
                         int building_id,
                         const std::vector<int>& task_list) :
  building_id_{building_id} {
  for (int task : task_list) {
    Placement placement;
    placement.taskid = task;

    task_list_.push_back(placement);
  }

  left_ = std::vector<std::vector<int>>(inst_->GetNumTaskNodes(),
                                        std::vector<int>(inst_->GetNumTaskNodes(), 0));
  top_ = std::vector<std::vector<int>>(inst_->GetNumTaskNodes(),
                                       std::vector<int>(inst_->GetNumTaskNodes(), 0));
}

int SolBuilding::Size() const {
  return task_list_.size();
}

bool SolBuilding::ServeTaskNode(int task_node) const {
  return FindTaskNode(task_node) != -1;
}

int SolBuilding::FindTaskNode(int task_node) const {
  auto pos = std::find(task_list_.cbegin(), task_list_.cend(), Placement{task_node});
  if (pos != task_list_.cend()) {
    return std::distance(task_list_.cbegin(), pos);
  }

  return -1;
}

int SolBuilding::TaskNode(int index) const {
  return task_list_.at(index).taskid;
}

void SolBuilding::UpdatePosition() {
  for (int i = 0; i < task_list_.size(); i++) {
    auto placement = task_list_[i];
    task_position_[placement.taskid] = i;
  }
}

void SolBuilding::InsertTaskNode(int taskid, int index) {
  Placement placement;
  placement.taskid = taskid;

  task_list_.insert(task_list_.begin() + index, placement);
}

void SolBuilding::RemoveTaskNode(int taskid) {
  int index = FindTaskNode(taskid);
  RemoveTaskNodeByIndex(index);
}

void SolBuilding::RemoveTaskNodeByIndex(int index) {
  task_list_.erase(task_list_.begin() + index);
}

void SolBuilding::Decode() {}

void SolBuilding::PosRelation() {}

} // namespace loptw::alg
