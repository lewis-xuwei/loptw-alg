///======================================================
/// Project :   loptw-bnc
/// File    :   tasknode.cpp
///------------------------------------------------------
/// Time    :   2026/04/24 18:57:39
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#include <loptw/instance/tasknode.h>

namespace loptw::instance {

TaskNode::TaskNode(Index tasknode_id, double width, double length) :
  tasknode_id_{tasknode_id}, width_{width}, length_{length} {}

} // namespace loptw::instance
