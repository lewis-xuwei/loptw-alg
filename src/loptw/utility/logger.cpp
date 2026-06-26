///======================================================
/// Project :   loptw-bnc
/// File    :   logger.cpp
///------------------------------------------------------
/// Time    :   2026/04/26 11:20:49
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#include <loptw/utility/logger.h>

#include "logger_impl.h"

namespace loptw::utility {

std::shared_ptr<Logger> Logger::GetLogger(const std::string& name) {
  return std::make_shared<LoggerImpl>(name);
}

Loggable::Loggable() {
  LogConstruct();
}

Loggable::~Loggable() {}

void Loggable::LogConstruct() {
  logger_ = Lazy<Logger>([this]() -> std::shared_ptr<Logger> {
    std::string module_name = Type::NameOf(this);
    return Logger::GetLogger(module_name);
  });
}

} // namespace loptw::utility
