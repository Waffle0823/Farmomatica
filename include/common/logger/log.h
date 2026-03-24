#pragma once

#include <memory.h>
#include <memory>
#include <spdlog/logger.h>
#include <spdlog/spdlog.h>

namespace farmomatica {

class Log {
public:
  static void Init();

  static std::shared_ptr<spdlog::logger> &GetLogger() noexcept;

private:
  static std::shared_ptr<spdlog::logger> s_Logger;
};

} // namespace farmomatica

#ifndef NDEBUG
#define LOG_TRACE(...) farmomatica::Log::GetLogger()->trace(__VA_ARGS__)
#define LOG_DEBUG(...) farmomatica::Log::GetLogger()->debug(__VA_ARGS__)
#else
#define LOG_TRACE(...) ((void)0)
#define LOG_DEBUG(...) ((void)0)
#endif

#define LOG_INFO(...) farmomatica::Log::GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...) farmomatica::Log::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) farmomatica::Log::GetLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) farmomatica::Log::GetLogger()->critical(__VA_ARGS__)
