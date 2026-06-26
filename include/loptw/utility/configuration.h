///======================================================
/// Project :   loptw-bnc
/// File    :   configuration.h
///------------------------------------------------------
/// Time    :   2026/04/26 10:45:54
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#ifndef __LOPTW_BNC_INCLUDE_LOPTW_UTILITY_CONFIGURATION_H__
#define __LOPTW_BNC_INCLUDE_LOPTW_UTILITY_CONFIGURATION_H__

#include <memory>
#include <string>

namespace loptw::utility {

class Configuration {
public:
  static std::shared_ptr<Configuration> GetInstance();
  virtual std::string GetValue(const std::string &name,
                               const std::string &default_value = "") const = 0;
};

} // namespace loptw::utility

#endif // __LOPTW_BNC_INCLUDE_LOPTW_UTILITY_CONFIGURATION_H__
