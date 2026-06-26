///======================================================
/// Project :   loptw-bnc
/// File    :   logger_impl.cpp
///------------------------------------------------------
/// Time    :   2026/04/26 11:22:14
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#include <map>
#include <memory>

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>


#include "logger_impl.h"

#include <loptw/utility/configuration.h>

namespace loptw::utility {

static LogLevel FromString(const std::string &level) {
  static std::map<std::string, LogLevel> __level_string_map{
      {"Trace", LogLevel::Trace}, {"Debug", LogLevel::Debug},
      {"Info", LogLevel::Info},   {"Warn", LogLevel::Warn},
      {"Error", LogLevel::Error}, {"Critical", LogLevel::Critical},
      {"Off", LogLevel::Off}};

  if (__level_string_map.find(level) != __level_string_map.cend()) {
    return __level_string_map[level];
  }

  return LogLevel::Info;
}

std::shared_ptr<spdlog::logger> LoggerImpl::GetSpdLogInstance() {
  // 获取日志目录 级别
  auto config = Configuration::GetInstance();
  auto level = config->GetValue("log.level", "Info");
  auto log_level = FromString(level);
  auto appender = config->GetValue("log.appender", "logs/logfile.txt");

  std::string log_pattern{"[%Y-%m-%d %H:%M:%S.%e %z] [%t] [%l] %v"};
  auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
  console_sink->set_level(spdlog::level::info);
  console_sink->set_pattern(log_pattern);

  auto file_sink =
      std::make_shared<spdlog::sinks::basic_file_sink_mt>(appender, false);
  file_sink->set_level(spdlog::level::info);
  file_sink->set_pattern(log_pattern);

  static spdlog::logger spd_logger("multi_sink", {console_sink, file_sink});
  auto logger_ptr = std::make_shared<spdlog::logger>(spd_logger);

  logger_ptr->set_level(static_cast<spdlog::level::level_enum>(log_level));

  return logger_ptr;
}

LoggerImpl::LoggerImpl(const std::string &module_name, LogLevel level)
    : module_name_{module_name}, level_{level} {
  spd_logger_ = GetSpdLogInstance();
}

LoggerImpl::~LoggerImpl() {}

void LoggerImpl::SetLevel(LogLevel level) {
  spd_logger_->set_level(static_cast<spdlog::level::level_enum>(level));
}

void LoggerImpl::Critical(const std::string &msg, int line) {
  Log(LogLevel::Critical, msg, line);
}

void LoggerImpl::Error(const std::string &msg, int line) {
  Log(LogLevel::Error, msg, line);
}

void LoggerImpl::Warn(const std::string &msg, int line) {
  Log(LogLevel::Warn, msg, line);
}
void LoggerImpl::Info(const std::string &msg, int line) {
  Log(LogLevel::Info, msg, line);
}
void LoggerImpl::Debug(const std::string &msg, int line) {
  Log(LogLevel::Debug, msg, line);
}
void LoggerImpl::Trace(const std::string &msg, int line) {
  Log(LogLevel::Trace, msg, line);
}

void LoggerImpl::Log(LogLevel level, const std::string &msg, int line) {
  spd_logger_->log(static_cast<spdlog::level::level_enum>(level),
                   "[{}:{}] - {}", module_name_, line, msg);
}

} // namespace loptw::utility
