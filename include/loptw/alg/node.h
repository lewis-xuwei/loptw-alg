///======================================================
/// Project :   loptw-alg
/// File    :   node.h
///------------------------------------------------------
/// Time    :   2026/06/28 13:26:54
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

namespace loptw::alg {

struct Node {
  // task node's id
  int id;

  // left coordination when decoding
  // center coordination when solving LP
  double x = 0;

  // bottom coordination when decoding
  // center coordination when solving LP
  double y = 0;

  // whether is rotated
  bool rotated = false;

  bool operator==(const Node& other) const {
    return id == other.id;
  }
};

} // namespace loptw::alg
