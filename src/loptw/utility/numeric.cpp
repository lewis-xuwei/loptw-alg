///======================================================
/// Project :   loptw-bnc
/// File    :   numeric.cpp
///------------------------------------------------------
/// Time    :   2026/05/20 14:04:00
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#include <cmath>

#include <loptw/utility/numeric.h>

namespace loptw::utility {

bool Numeric::IsZero(double val, double toleration) {
  return std::abs(val) < toleration;
}

bool Numeric::Equal(double left, double right, double toleration) {
  return IsZero(left - right, toleration);
}

bool Numeric::EqualSlightLess(double val, double right, double toleration) {
  return right - val < toleration;
}

bool Numeric::EqualSlightGreater(double val, double left, double toleration) {
  return val - left < toleration;
}

bool Numeric::IsIntegral(double val, double toleration) {
  return IsZero(val - std::round(val), toleration);
}

int Numeric::IndexOfMostFractional(const std::vector<double> &vals,
                                   const std::vector<int> &int_vars) {
  int index = -1;
  double max_dis_to_half = std::numeric_limits<double>::infinity();
  for (int i : int_vars) {
    double val = vals[i];
    double fraction = val - std::floor(val);
    double dis_to_half = std::abs(0.5 - fraction);
    if (dis_to_half < max_dis_to_half) {
      max_dis_to_half = dis_to_half;
      index = i;
    }
  }
  return index;
}

std::vector<int> Numeric::Ones(int n) { return std::vector<int>(n, 1); }

std::vector<double> Numeric::Zeros(int n) {
  return std::vector<double>(n, 0.0);
}

std::vector<double> Numeric::Abs(const std::vector<double> &vals) {
  std::vector<double> result(vals.size());
  for (size_t i = 0; i < vals.size(); ++i) {
    result[i] = std::abs(vals[i]);
  }
  return result;
}

} // namespace loptw::utility
