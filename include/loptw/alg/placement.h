///======================================================
/// Project :   loptw-alg
/// File    :   placement.h
///------------------------------------------------------
/// Time    :   2026/06/28 13:26:54
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

namespace loptw::alg {

struct Placement {
  // task node's id
  int taskid;

  // left coordination when decoding
  // center coordination when solving LP
  double x = 0;

  // bottom coordination when decoding
  // center coordination when solving LP
  double y = 0;

  // whether is rotated
  bool rotated = false;

  bool operator==(const Placement& other) const {
    return taskid == other.taskid;
  }
};

} // namespace loptw::alg
