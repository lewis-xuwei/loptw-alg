///======================================================
/// Project :   loptw-bnc
/// File    :   configuration.cpp
///------------------------------------------------------
/// Time    :   2026/04/26 11:32:58
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#include <memory>

#include "configuration_impl.hpp"

#include <loptw/utility/configuration.h>

namespace loptw::utility {

std::shared_ptr<Configuration> Configuration::GetInstance() {
  static ConfigurationImpl config("application.toml");
  auto config_ptr = std::make_shared<ConfigurationImpl>(config);
  return std::dynamic_pointer_cast<Configuration>(config_ptr);
}

} // namespace loptw::utility
