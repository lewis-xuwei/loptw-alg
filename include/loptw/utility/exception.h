///======================================================
/// Project :   loptw-bnc
/// File    :   exception.h
///------------------------------------------------------
/// Time    :   2026/04/26 10:45:14
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#ifndef __LOPTW_BNC_INCLUDE_LOPTW_UTILITY_EXCEPTION_H__
#define __LOPTW_BNC_INCLUDE_LOPTW_UTILITY_EXCEPTION_H__

#include <string>

namespace loptw::utility {

class Exception {
public:
  explicit Exception(const std::string& message);
  explicit Exception(const std::string& message, int code);
  virtual ~Exception();

  virtual int GetCode() const;
  virtual std::string GetMessage() const;

private:
  int code_;
  std::string message_;
};

} // namespace loptw::utility

#endif // __LOPTW_BNC_INCLUDE_LOPTW_UTILITY_EXCEPTION_H__
