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

class Skyline {
public:
  static std::vector<std::vector<double>> GetSkyline(std::vector<std::vector<double>>& buildings);
};

} // namespace loptw::alg

#endif // __LOPTW_ALG_INCLUDE_LOPTW_ALG_SKYLINE_HPP__
