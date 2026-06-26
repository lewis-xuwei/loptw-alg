///======================================================
/// Project :   loptw-bnc
/// File    :   test_timer.cpp
///------------------------------------------------------
/// Time    :   2026/06/14 13:46:11
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#include <memory>
#include <thread>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <loptw/utility/timer.h>

TEST_CASE("Test Class `loptw::utility::Timer'") {
  using namespace loptw::utility;
  for (int i = 1; i < 5; ++i) {
    double sleeptime = Timer::Ellapsed(
        [&i] { std::this_thread::sleep_for(std::chrono::seconds(i)); });
    REQUIRE(sleeptime > i);
  }

  Timer timer;
  timer.Start();
  int a = 1;
  std::this_thread::sleep_for(std::chrono::seconds(a));
  REQUIRE(timer.Ellapsed() > a);
  std::this_thread::sleep_for(std::chrono::seconds(2 * a));
  REQUIRE(timer.Ellapsed() > 3 * a);
}