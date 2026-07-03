///======================================================
/// Project :   loptw-alg
/// File    :   sol_building.cpp
///------------------------------------------------------
/// Time    :   2026/06/29 15:22:09
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#include <loptw/alg/skyline.h>
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

// skyline algorithm
void SolBuilding::Decode() {
  using namespace loptw::alg;

  auto building = inst_->buildings().at(building_id_);
  double W = building->width_;
  double H = building->length_;
  double L = building->left_coord_;
  double B = building->bottom_coord_;

  std::vector<Skyline> skylines({Skyline{L, L + W, B}});
  // place task node by order
  for (int i = 0; i < task_list_.size(); i++) {
    task_list_[i].placed = false; // initialize the placement status

    double w_i = inst_->tasknodes().at(task_list_[i].taskid)->width_;
    double h_i = inst_->tasknodes().at(task_list_[i].taskid)->length_;
    if (task_list_[i].rotated) {
      std::swap(w_i, h_i);
    }

    int s = -1;
    double min_h = std::numeric_limits<double>::infinity();

    std::sort(skylines.begin(), skylines.end(), [](const Skyline& a, const Skyline& b) {
      return a.left < b.left;
    });

    // find the most left position with the lowest height
    for (int j = 0; j < skylines.size(); j++) {
      if (Skylines::Locate(skylines, w_i, h_i, H, j)) {
        if (skylines[j].height < min_h) {
          min_h = skylines[j].height;
          s = j;
        }
      }
    }

    if (s != -1) {
      task_list_[i].placed = true;
      task_list_[i].x = skylines[s].left;
      task_list_[i].y = skylines[s].height;

      Skyline new_skyline{skylines[s].left, skylines[s].left + w_i, skylines[s].height + h_i};
      skylines.push_back(new_skyline);

      Skylines::MergeSkyline(skylines, L, L + W);
    }
  }
}

void SolBuilding::PosRelation() {}

} // namespace loptw::alg
