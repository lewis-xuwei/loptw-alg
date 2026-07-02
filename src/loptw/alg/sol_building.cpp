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
    Node node;
    node.id = task;

    task_list_.push_back(node);
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
  auto pos = std::find(task_list_.cbegin(), task_list_.cend(), Node{task_node});
  if (pos != task_list_.cend()) {
    return std::distance(task_list_.cbegin(), pos);
  }

  return -1;
}

int SolBuilding::TaskNode(int index) const {
  return task_list_.at(index).id;
}

void SolBuilding::UpdatePosition() {
  for (int i = 0; i < task_list_.size(); i++) {
    auto task_node = task_list_[i];
    task_position_[task_node.id] = i;
  }
}

void SolBuilding::InsertTaskNode(int task, int pos) {
  Node node;
  node.id = task;

  task_list_.insert(task_list_.begin() + pos, node);
}

void SolBuilding::RemoveTaskNode(int task) {
  int pos = FindTaskNode(task);
  RemoveTaskNodeByPos(pos);
}

void SolBuilding::RemoveTaskNodeByPos(int pos) {
  task_list_.erase(task_list_.begin() + pos);
}

void SolBuilding::Decode() {}

void SolBuilding::PosRelation() {}

} // namespace loptw::alg
