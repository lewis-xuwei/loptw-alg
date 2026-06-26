///======================================================
/// Project :   loptw-bnc
/// File    :   type.cpp
///------------------------------------------------------
/// Time    :   2026/04/26 10:50:49
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#include <loptw/utility/type.h>

#ifndef _MSC_VER
#  include <cxxabi.h>
#endif

namespace loptw::utility {

const std::string Type::Demangling(const char *name) {
#ifndef _MSC_VER
  int status = -4;

  char *res = abi::__cxa_demangle(name, NULL, NULL, &status);

  const char *const demangled_name = (status == 0) ? res : name;

  std::string ret_val(demangled_name);

  free(res);

  return ret_val;
#else
  return std::string(name).substr(6);
#endif // _MSC_VER
}

} // namespace loptw::utility
