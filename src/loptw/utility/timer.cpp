///======================================================
/// Project :   loptw-bnc
/// File    :   timer.cpp
///------------------------------------------------------
/// Time    :   2026/06/14 13:07:17
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#include <loptw/utility/timer.h>

namespace loptw::utility {

double Timer::Ellapsed(const std::function<void()> &runnable) {
  auto start = std::chrono::steady_clock::now();

  runnable();

  auto end = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  return elapsed.count();
}

void Timer::Start() {
  start_timepoint_ = std::chrono::steady_clock::now();
}

double Timer::Ellapsed() const {
  auto end_timepoint_ = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed = end_timepoint_ - start_timepoint_;
  return elapsed.count();
}

} // namespace loptw::utility