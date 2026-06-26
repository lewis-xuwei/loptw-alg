///======================================================
/// Project :   loptw-bnc
/// File    :   timer.h
///------------------------------------------------------
/// Time    :   2026/06/14 13:07:36
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#ifndef __LOPTW_BNC_INCLUDE_LOPTW_UTILITY_TIMER_H__
#define __LOPTW_BNC_INCLUDE_LOPTW_UTILITY_TIMER_H__

#include <chrono>
#include <functional>

namespace loptw::utility {

/// @brief second-based timer
class Timer {
public:
  static double Ellapsed(const std::function<void()> &runnable);

  Timer() = default;
  ~Timer() = default;
  void Start();
  double Ellapsed() const;

private:
  std::chrono::steady_clock::time_point start_timepoint_;
};

} // namespace loptw::utility

#endif // __LOPTW_BNC_INCLUDE_LOPTW_UTILITY_TIMER_H__
