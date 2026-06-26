///======================================================
/// Project :   loptw-bnc
/// File    :   instance.h
///------------------------------------------------------
/// Time    :   2026/04/24 19:06:49
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#ifndef __LOPTW_BNC_INCLUDE_LOPTW_INSTANCE_INSTANCE_H__
#define __LOPTW_BNC_INCLUDE_LOPTW_INSTANCE_INSTANCE_H__

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <loptw/instance/building.h>
#include <loptw/instance/tasknode.h>
#include <loptw/instance/workflow.h>

namespace loptw::instance {

class Instance {
public:
  template <typename T>
  using Pool = std::map<typename T::Key, std::shared_ptr<T>>;

public:
  Instance();

  /// @brief Set the path of json data
  /// @param path
  void set_instance_path(const std::string path);
  const std::string &instance_path() const;
  const Pool<Building> &buildings() const;
  const Pool<TaskNode> &tasknodes() const;
  const Pool<Workflow> &workflows() const;

  /// @brief Read instance from path
  /// @param path
  /// @return
  static std::shared_ptr<Instance> FromPath(const std::string path);

  /// @brief Check whether the data is consistent
  /// @return true when data is consistent, otherwise false
  bool Validate() const;

public:
  size_t GetNumBuildings() const;
  size_t GetNumTaskNodes() const;
  size_t GetNumWorkflows() const;

public:
  /// @brief Add a building
  /// @param building
  /// @param overwrite
  /// @return true if a build object is added, otherwise false
  bool AddBuilding(const std::shared_ptr<Building> building,
                   bool overwrite = false);

  /// @brief Remove a builing with building id
  /// @param building_id
  /// @return true if a building object is removed, otherwise false
  bool RemoveBuilding(const Index building_id);

  /// @brief Add a task node
  /// @param tasknode
  /// @param overwrite
  /// @return true if a task node is added, otherwise false
  bool AddTaskNode(const std::shared_ptr<TaskNode> tasknode,
                   bool overwrite = false);

  /// @brief Remove a task node with tasknode_id
  /// @param tasknode_id
  /// @return true if a task node object is removed, otherwise false
  bool RemoveTaskNode(const Index tasknode_id);

  /// @brief Add a workflow
  /// @param workflow
  /// @param overwrite
  /// @return true if a workflow is added, otherwise false
  bool AddWorkflow(const std::shared_ptr<Workflow> workflow,
                   bool overwrite = false);

  /// @brief Remove a workflow from source to target
  /// @param source
  /// @param target
  /// @return true if a workflow is added, otherwise false
  bool RemoveWorkflow(Index source, Index target);

private:
  Pool<Building> buildings_;
  Pool<TaskNode> tasknodes_;
  Pool<Workflow> workflows_;

private:
  std::string instance_path_;
};

} // namespace loptw::instance

#endif // __LOPTW_BNC_INCLUDE_LOPTW_INSTANCE_INSTANCE_H__
