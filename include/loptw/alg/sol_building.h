///======================================================
/// Project :   loptw-alg
/// File    :   sol_building.h
///------------------------------------------------------
/// Time    :   2026/06/28 11:27:40
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#include <unordered_map>
#include <vector>

#include <loptw/alg/placement.h>
#include <loptw/instance/instance.h>

namespace loptw::alg {

// building_id
// task-list
// i-j relation by greedy decoding
class SolBuilding {
public:
  SolBuilding(std::shared_ptr<instance::Instance> inst,
              int building_id,
              const std::vector<int>& task_list,
              std::shared_ptr<std::vector<std::vector<int>>> left_,
              std::shared_ptr<std::vector<std::vector<int>>> top_);

public:
  int Size() const;
  bool ServeTaskNode(int taskid) const;
  int FindTaskNode(int taskid) const;
  int TaskNode(int index) const;
  void UpdatePosition();

  void InsertTaskNode(int taskid, int index);
  void RemoveTaskNode(int taskid);
  void RemoveTaskNodeByIndex(int index);

public:
  // place the task list by given order
  void Decode();
  // analyze the position relationship
  void PosRelation();

private:
  std::shared_ptr<instance::Instance> inst_;

private:
  int building_id_;
  std::vector<Placement> task_list_;
  std::unordered_map<int, int> task_position_;

  // the whole solution shares the same memory for left and top relation
  std::shared_ptr<std::vector<std::vector<int>>> left_; // left[i][j] = 1 => i is in the left of j
  std::shared_ptr<std::vector<std::vector<int>>> top_;  // top[i][j] = 1 => i is in the top of j
};

} // namespace loptw::alg
