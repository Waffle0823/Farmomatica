#include <spdlog/async.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "common/logger/log.h"

namespace farmomatica {

std::shared_ptr<spdlog::logger> Log::s_Logger;

void Log::Init() {
  spdlog::init_thread_pool(8192, 1);

  auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
  console_sink->set_pattern("[%T] [%^%l%$] %v");

  auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
      "logs/game.log", 5 * 1024 * 1024, 3);
  file_sink->set_pattern("[%T] [%l] %v");

  std::vector<spdlog::sink_ptr> sinks{console_sink, file_sink};

  s_Logger = std::make_shared<spdlog::async_logger>(
      "GAME", sinks.begin(), sinks.end(), spdlog::thread_pool(),
      spdlog::async_overflow_policy::block);

  spdlog::register_logger(s_Logger);

  s_Logger->set_level(spdlog::level::trace);
  s_Logger->flush_on(spdlog::level::warn);
}

std::shared_ptr<spdlog::logger> &Log::GetLogger() noexcept { return s_Logger; }

} // namespace farmomatica
