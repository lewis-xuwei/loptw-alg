///======================================================
/// Project :   loptw-bnc
/// File    :   logger_impl.h
///------------------------------------------------------
/// Time    :   2026/04/26 11:23:10
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#ifndef __LOPTW_BNC_SRC_LOPTW_UTILITY_LOGGER_IMPL_H__
#define __LOPTW_BNC_SRC_LOPTW_UTILITY_LOGGER_IMPL_H__

#include <memory>

#include <spdlog/spdlog.h>

#include <loptw/utility/logger.h>

namespace loptw::utility {

class LoggerImpl : public Logger {
public:
  LoggerImpl(const std::string &module_name, LogLevel level = LogLevel::Info);
  ~LoggerImpl();

  static std::shared_ptr<spdlog::logger> GetSpdLogInstance();

public:
  virtual void SetLevel(LogLevel level) override;
  virtual void Trace(const std::string &msg, int line) override;
  virtual void Debug(const std::string &msg, int line) override;
  virtual void Info(const std::string &msg, int line) override;
  virtual void Warn(const std::string &msg, int line) override;
  virtual void Error(const std::string &msg, int line) override;
  virtual void Critical(const std::string &msg, int line) override;

private:
  void Log(LogLevel level, const std::string &msg, int line);

private:
  std::string module_name_;
  LogLevel level_;
  std::shared_ptr<spdlog::logger> spd_logger_;
};

} // namespace loptw::utility

#endif // __LOPTW_BNC_SRC_LOPTW_UTILITY_LOGGER_IMPL_H__
