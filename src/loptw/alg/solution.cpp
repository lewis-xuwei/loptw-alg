///======================================================
/// Project :   loptw-alg
/// File    :   solution.cpp
///------------------------------------------------------
/// Time    :   2026/07/05 15:51:26
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#include <loptw/alg/solution.h>

namespace loptw::alg {

Solution::Solution(std::shared_ptr<instance::Instance> inst, std::shared_ptr<Parameter> parameter) :
  inst_{inst}, parameter_{parameter} {
  T = inst_->GetNumBuildings();
  N = inst_->GetNumTaskNodes();
  F = inst_->GetNumWorkflows();
}

// Calculate the objective
double Solution::Objective() const {
  return obj_;
}

// Print the result
void Solution::PrintResult() const {}

bool Solution::operator<(const Solution& solution) const {
  return obj_ < solution.obj_;
}

std::shared_ptr<Solution> Solution::Copy() {
  return std::make_shared<Solution>(*this);
}

// analyze l,m,z,p,r
void Solution::Decode() {
  left_ = std::vector<std::vector<int>>(N, std::vector<int>(N, 0));
  top_ = std::vector<std::vector<int>>(N, std::vector<int>(N, 0));
  z_ = std::vector<std::vector<int>>(N, std::vector<int>(T, 0));
  p_ = std::vector<int>(T, 0);
  r_ = std::vector<int>(N, 0);
  // to determine l,m
  for (int t = 0; t < inst_->GetNumBuildings(); ++t) {
    buildings_[t].Decode();
    buildings_[t].PosRelation(left_, top_);
  }

  for (int t = 0; t < T; ++t) {
    for (auto& placement : buildings_[t].task_list_) {
      int taskid = placement.taskid;
      if (placement.placed) {
        z_[taskid][t] = 1;
        p_[t] = 1; // any placement would trigger
        if (placement.rotated) {
          r_[taskid] = 1;
        }
      }
    }
  }
}

} // namespace loptw::alg
