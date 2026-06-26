///======================================================
/// Project :   loptw-bnc
/// File    :   workflow.cpp
///------------------------------------------------------
/// Time    :   2026/04/24 18:18:51
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#include <loptw/instance/workflow.h>

namespace loptw::instance {

Workflow::Workflow(Index source, Index target, double quantity)
    : source_{source}, target_{target}, quantity_{quantity} {}

} // namespace loptw::instance
