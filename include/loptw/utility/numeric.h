///======================================================
/// Project :   loptw-bnc
/// File    :   numeric.h
///------------------------------------------------------
/// Time    :   2026/05/20 14:00:15
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#ifndef __LOPTW_BNC_INCLUDE_LOPTW_UTILITY_NUMERIC_H__
#define __LOPTW_BNC_INCLUDE_LOPTW_UTILITY_NUMERIC_H__

#include <vector>

namespace loptw::utility {

class Numeric {
public:
  /// @brief whether $val==0$
  static bool IsZero(double val, double toleration = 1e-9);

  /// @brief whether $left==right$
  static bool Equal(double left, double right, double toleration = 1e-9);

  /// @brief whether $val$ is slightly less equal to $right^-$
  static bool EqualSlightLess(double val, double right,
                              double toleration = 1e-9);

  /// @brief whether $val$ is slightly greater equal to $right^-$
  static bool EqualSlightGreater(double val, double left,
                                 double toleration = 1e-9);

  /// @brief whether $val$ is integral
  static bool IsIntegral(double val, double toleration = 1e-9);

  /// @brief Find the index of the most fractional variable
  static int IndexOfMostFractional(const std::vector<double> &vals,
                                   const std::vector<int> &int_vars);

  static std::vector<int> Ones(int n);

  static std::vector<double> Zeros(int n);

  static std::vector<double> Abs(const std::vector<double> &vals);
};

} // namespace loptw::utility

#endif // __LOPTW_BNC_INCLUDE_LOPTW_UTILITY_NUMERIC_H__
