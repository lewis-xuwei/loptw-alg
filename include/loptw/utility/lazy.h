///======================================================
/// Project :   loptw-bnc
/// File    :   lazy.h
///------------------------------------------------------
/// Time    :   2026/04/26 11:10:38
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#ifndef __LOPTW_BNC_INCLUDE_LOPTW_UTILITY_LAZY_H__
#define __LOPTW_BNC_INCLUDE_LOPTW_UTILITY_LAZY_H__

#include <memory>
#include <mutex>

#include <loptw/utility/action.h>

namespace loptw ::utility {

template <typename T> class Lazy;

// State of lazy object
template <typename T> class LazyState {
public:
  virtual std::shared_ptr<T> &Get(Lazy<T> *lazy) = 0;
  virtual bool IsInitialized() = 0;
};

// State of initialized object
template <typename T> class LazyInitialized : public LazyState<T> {
public:
  LazyInitialized(std::shared_ptr<T> val = nullptr) : val_(val) {}

  std::shared_ptr<T> &Get(Lazy<T> *lazy) override { return val_; }

  bool IsInitialized() override { return true; }

private:
  std::shared_ptr<T> val_;
};

// State of await object
template <typename T>
class LazyAwait : public LazyState<T>, protected Action<std::shared_ptr<T>()> {
public:
  LazyAwait(std::function<std::shared_ptr<T>()> action = nullptr)
      : Action<std::shared_ptr<T>()>(action) {}

  std::shared_ptr<T> &Get(Lazy<T> *lazy) override {
    if (!initialized_) {
      mtx_->lock();

      if (!initialized_) {
        lazy->SetValue(Action<std::shared_ptr<T>()>::action_());
        initialized_ = true;
      }

      mtx_->unlock();
    }
    return lazy->Get();
  }

  bool IsInitialized() override { return initialized_; }

private:
  bool initialized_ = false;
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
};

template <typename T> class Lazy {
public:
  Lazy(std::function<std::shared_ptr<T>()> action = nullptr) {
    if (action == nullptr) {
      state = std::make_shared<LazyInitialized<T>>(nullptr);
    } else {
      state = std::make_shared<LazyAwait<T>>(action);
    }
  }

  void SetValue(std::shared_ptr<T> val = nullptr) {
    state = std::make_shared<LazyInitialized<T>>(val);
  }

  std::shared_ptr<T> &Get() {
    std::shared_ptr<LazyState<T>> tmp = state;
    return tmp->Get(this);
  }

  std::shared_ptr<T> operator->() { return this->Get(); }

  bool IsInitialized() const { return state->IsInitialized(); }

private:
  std::shared_ptr<LazyState<T>> state;
};

} // namespace loptw::utility

#endif // __LOPTW_BNC_INCLUDE_LOPTW_UTILITY_LAZY_H__
