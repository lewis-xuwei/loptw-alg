///======================================================
/// Project :   loptw-bnc
/// File    :   tasknodes.h
///------------------------------------------------------
/// Time    :   2026/04/24 18:32:46
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#ifndef __LOPTW_BNC_INCLUDE_LOPTW_INSTANCE_TASKNODE_H__
#define __LOPTW_BNC_INCLUDE_LOPTW_INSTANCE_TASKNODE_H__

#include <loptw/instance/types.h>

namespace loptw::instance {

class TaskNode {
public:
  using Key = Index;

public:
  TaskNode() = delete;
  TaskNode(Index tasknode_id, double width, double length);

public:
  Index tasknode_id_;
  double width_;
  double length_;
};

} // namespace loptw::instance

#endif // __LOPTW_BNC_INCLUDE_LOPTW_INSTANCE_TASKNODE_H__
