///======================================================
/// Project :   loptw-bnc
/// File    :   helper.h
///------------------------------------------------------
/// Time    :   2026/04/24 18:17:01
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#ifndef __LOPTW_BNC_TESTINGS_INCLUDE_HELPER_HPP__
#define __LOPTW_BNC_TESTINGS_INCLUDE_HELPER_HPP__

#include <cstdlib>

bool inline NearlyEqual(double a, double b, double tol = 1E6) {
  return std::abs(a - b) < tol;
}

#endif // __LOPTW_BNC_TESTINGS_INCLUDE_HELPER_HPP__
