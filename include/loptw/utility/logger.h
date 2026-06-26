///======================================================
/// Project :   loptw-bnc
/// File    :   logger.h
///------------------------------------------------------
/// Time    :   2026/04/26 10:36:49
/// Author  :   xuwei <lewis.xuwei@outlook.com>
///
///           COPYRIGHT @ 2026
///======================================================

#ifndef __LOPTW_BNC_INCLUDE_LOPTW_UTILITY_LOGGER_H__
#define __LOPTW_BNC_INCLUDE_LOPTW_UTILITY_LOGGER_H__

#include <memory>
#include <string>

#include <loptw/utility/lazy.h>
#include <loptw/utility/type.h>

#define LogCritical(logger, message) logger->Critical(message, __LINE__)
#define LogError(logger, message)    logger->Error(message, __LINE__)
#define LogWarn(logger, message)     logger->Warn(message, __LINE__)
#define LogInfo(logger, message)     logger->Info(message, __LINE__)
#define LogDebug(logger, message)    logger->Debug(message, __LINE__)
#define LogTrace(logger, message)    logger->Trace(message, __LINE__)

namespace loptw::utility {

enum class LogLevel : int {
  Trace,
  Debug,
  Info,
  Warn,
  Error,
  Critical,
  Off,
  nLevels
};

class Logger {
public:
  template <class T>
  static std::shared_ptr<Logger> GetLogger();
  static std::shared_ptr<Logger> GetLogger(const std::string& name);

public:
  virtual void SetLevel(LogLevel level) = 0;
  virtual void Trace(const std::string& msg, int line) = 0;
  virtual void Debug(const std::string& msg, int line) = 0;
  virtual void Info(const std::string& msg, int line) = 0;
  virtual void Warn(const std::string& msg, int line) = 0;
  virtual void Error(const std::string& msg, int line) = 0;
  virtual void Critical(const std::string& msg, int line) = 0;
};

template <class T>
inline std::shared_ptr<Logger> Logger::GetLogger() {
  return GetLogger(Type::NameOf<T>());
}

class Loggable {
protected:
  Lazy<Logger> logger_;

protected:
  Loggable();
  ~Loggable();
  virtual void LogConstruct();
};

} // namespace loptw::utility

#endif // __LOPTW_BNC_INCLUDE_LOPTW_UTILITY_LOGGER_H__
