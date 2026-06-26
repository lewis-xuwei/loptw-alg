///======================================================
/// Project :   loptw-bnc
/// File    :   action.h
///------------------------------------------------------
/// Time    :   2026/04/26 11:01:01
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#ifndef __LOPTW_BNC_INCLUDE_LOPTW_UTILITY_ACTION_H__
#define __LOPTW_BNC_INCLUDE_LOPTW_UTILITY_ACTION_H__

#define DEFER_1(x, y) x##y
#define DEFER_2(x, y) DEFER_1(x, y)
#define DEFER_3(x) DEFER_2(x, __COUNTER__)
#define defer(code) auto DEFER_3(_defer_) = loptw::utility::Defer(code)

#include <functional>
#include <memory>

namespace loptw::utility {

template <typename T> class Action {
protected:
  Action(std::function<T> action) : action_(action) {}

protected:
  std::function<T> action_;
};

class DeferedAction {
public:
  DeferedAction(std::function<void()> defer_action)
      : defer_action_(defer_action) {}

  ~DeferedAction() { defer_action_(); }

private:
  std::function<void()> defer_action_;
};

std::shared_ptr<void> inline Defer(std::function<void()> defer_action) {
  return std::make_shared<DeferedAction>(defer_action);
}

} // namespace loptw::utility

#endif // __LOPTW_BNC_INCLUDE_LOPTW_UTILITY_ACTION_H__
