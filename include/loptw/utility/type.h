///======================================================
/// Project :   loptw-bnc
/// File    :   type.h
///------------------------------------------------------
/// Time    :   2026/04/26 10:49:14
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#ifndef __LOPTW_BNC_INCLUDE_LOPTW_UTILITY_TYPE_H__
#define __LOPTW_BNC_INCLUDE_LOPTW_UTILITY_TYPE_H__

#include <string>
#include <typeinfo>

namespace loptw::utility {

class Type {
public:
  static const std::string Demangling(const char *name);

public:
  template <class T> static const std::type_info TypeInfo() {
    return typeid(T);
  }

  template <class T> static const std::string NameOf() {
    return Demangling(typeid(T).name());
  }

  template <class T> static const std::string NameOf(T *p) {
    return Demangling(typeid(*p).name());
  }
};

} // namespace loptw::utility

#endif // __LOPTW_BNC_INCLUDE_LOPTW_UTILITY_TYPE_H__
