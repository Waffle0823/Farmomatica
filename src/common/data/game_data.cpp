#include <filesystem>
#include <stdexcept>

#include "common/data/game_data.h"
#include "common/logger/log.h"
#include "common/settings/global_settings.h"

namespace fs = std::filesystem;

namespace farmomatica {

namespace {
fs::path GetGlobalPath() {
  fs::path path;

#if defined(_WIN32) || defined(_WIN64)
  const char *appdata = std::getenv("APPDATA");
  if (appdata) {
    path = fs::path(appdata) / config::APPLICATION_NAME;
  } else {
    LOG_CRITICAL("Failed to find APPDATA environment variable on Windows");
    throw std::runtime_error("Failed to find config path");
  }

#elif defined(__APPLE__)
  const char *home = std::getenv("HOME");
  if (home) {
    path = fs::path(home) / "Library" / "Application Support" /
           config::APPLICATION_NAME;
  } else {
    LOG_CRITICAL("Failed to find HOME environment variable on macOS");
    throw std::runtime_error("Failed to find config path");
  }

#elif defined(__linux__) || defined(__unix__)
  const char *home = std::getenv("HOME");
  if (home) {
    path = fs::path(home) / ".local" / "share" / config::APPLICATION_NAME;
  } else {
    LOG_CRITICAL("Failed to find HOME environment variable on Linux/Unix");
    throw std::runtime_error("Failed to find config path");
  }

#endif

  if (path.empty()) {
    LOG_CRITICAL("Unsupported operating system detected");
    throw std::runtime_error("Unsupported OS");
  }

  return path;
}
} // anonymous namespace

namespace paths {

fs::path GetTexturesPath() {
  fs::path path = GetGlobalPath() / "assets" / "textures";
  if (!fs::exists(path)) {
    fs::create_directories(path);
  }
  return path;
}

fs::path GetShadersPath() {
  fs::path path = GetGlobalPath() / "assets" / "shaders";
  if (!fs::exists(path)) {
    fs::create_directories(path);
  }
  return path;
}

fs::path GetLogsPath() {
  fs::path path = GetGlobalPath() / "logs";
  if (!fs::exists(path)) {
    fs::create_directories(path);
  }
  return path;
}

fs::path GetSavesPath() {
  fs::path path = GetGlobalPath() / "saves";
  if (!fs::exists(path)) {
    fs::create_directories(path);
  }
  return path;
}

fs::path GetConfigPath() {
  fs::path path = GetGlobalPath() / "config";
  if (!fs::exists(path)) {
    fs::create_directories(path);
  }
  return path;
}

} // namespace paths
} // namespace farmomatica
