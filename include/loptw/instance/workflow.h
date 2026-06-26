///======================================================
/// Project :   loptw-bnc
/// File    :   workflow.h
///------------------------------------------------------
/// Time    :   2026/04/24 18:04:49
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#ifndef __LOPTW_BNC_INCLUDE_LOPTW_INSTANCE_WORKFLOW_H__
#define __LOPTW_BNC_INCLUDE_LOPTW_INSTANCE_WORKFLOW_H__

#include <utility>

#include <loptw/instance/types.h>

namespace loptw::instance {

class Workflow {
public:
  using Key = std::pair<Index, Index>;

public:
  Workflow() = delete;
  Workflow(Index source, Index target, double quantity);

public:
  Index source_;
  Index target_;
  double quantity_;
};

} // namespace loptw::instance

#endif // __LOPTW_BNC_INCLUDE_LOPTW_INSTANCE_WORKFLOW_H__
