///======================================================
/// Project :   loptw-bnc
/// File    :   configuration_impl.h
///------------------------------------------------------
/// Time    :   2026/04/26 11:35:14
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#ifndef __LOPTW_BNC_SRC_LOPTW_UTILITY_CONFIGURATION_IMPL_HPP__
#define __LOPTW_BNC_SRC_LOPTW_UTILITY_CONFIGURATION_IMPL_HPP__

#include <memory>

#include "cpptoml.h"

#include <loptw/utility/configuration.h>

namespace loptw::utility {

class ConfigurationImpl : public Configuration {
public:
  ConfigurationImpl(const std::string &config_file)
      : config_file_{config_file}, config_{nullptr} {
    config_ = cpptoml::parse_file(config_file_);
  }

  ~ConfigurationImpl() {}

  std::string GetValue(const std::string &name,
                       const std::string &default_value) const {
    if (nullptr != config_) {
      auto value = config_->get_qualified_as<std::string>(name);
      if (value) {
        return *value;
      }
    }

    return default_value;
  }

private:
  std::string config_file_;
  std::shared_ptr<cpptoml::table> config_;
};

} // namespace loptw::utility

#endif // __LOPTW_BNC_SRC_LOPTW_UTILITY_CONFIGURATION_IMPL_HPP__
