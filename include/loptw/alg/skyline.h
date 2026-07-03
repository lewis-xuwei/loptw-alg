///======================================================
/// Project :   loptw-alg
/// File    :   skyline.h
///------------------------------------------------------
/// Time    :   2026/07/02 17:00:46
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#ifndef __LOPTW_ALG_INCLUDE_LOPTW_ALG_SKYLINE_HPP__
#define __LOPTW_ALG_INCLUDE_LOPTW_ALG_SKYLINE_HPP__

#include <algorithm>
#include <queue>
#include <vector>

namespace loptw::alg {

struct Skyline {
  double left;
  double right;
  double height;
};

class Skylines {
public:
  static std::vector<std::vector<double>> Merge(std::vector<Skyline>& skylines);

  // find the position to place a rectangle with given width and height
  static bool Locate(const std::vector<Skyline>& skylines,
                     double width,
                     double height,
                     double H,
                     int index);
};

} // namespace loptw::alg

#endif // __LOPTW_ALG_INCLUDE_LOPTW_ALG_SKYLINE_HPP__
