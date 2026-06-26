///======================================================
/// Project :   loptw-bnc
/// File    :   exception.cpp
///------------------------------------------------------
/// Time    :   2026/04/26 11:06:17
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================
#include <loptw/utility/exception.h>

namespace loptw::utility {

Exception::Exception(const std::string& message) : message_{message} {}

Exception::Exception(const std::string& message, int code) :
  message_{message}, code_{code} {}

int Exception::GetCode() const {
  return code_;
}

std::string Exception::GetMessage() const {
  return message_;
}

Exception::~Exception() {}

} // namespace loptw::utility
