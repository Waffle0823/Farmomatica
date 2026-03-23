#include <filesystem>
#include <stdexcept>

#include "common/data/game_data.h"
#include "common/settings/global_settings.h"

namespace fs = std::filesystem;

namespace farmomatica {

fs::path GetGlobalPath() {
  fs::path path;

#if defined(_WIN32) || defined(_WIN64)
  const char *appdata = std::getenv("APPDATA");
  if (appdata)
    path = std::filesystem::path(appdata) / farmomatica::settings::global::application::NAME;
  else
    throw std::runtime_error("Failed to find config path");

#elif defined(__APPLE__)
  const char *home = std::getenv("HOME");
  if (home)
    path = std::filesystem::path(home) / "Library" / "Application Support" /
           farmomatica::settings::global::application::NAME;
  else
    throw std::runtime_error("Failed to find config path");

#elif defined(__linux__) || defined(__unix__)
  const char *home = std::getenv("HOME");
  if (home)
    path = std::filesystem::path(home) / ".local" / "share" /
           farmomatica::settings::global::application::NAME;
  else
    throw std::runtime_error("Failed to find config path");

#endif

  if (path.empty()) {
    throw std::runtime_error("Unsupported OS");
  }

  return path;
}

fs::path GameData::GetTexturesPath() {
  fs::path path = fs::current_path() / "assets" / "textures";
  if (!fs::exists(path)) {
    fs::create_directories(path);
  }
  return path;
}

fs::path GameData::GetShadersPath() {
  fs::path path = fs::current_path() / "assets" / "shaders";
  if (!fs::exists(path)) {
    fs::create_directories(path);
  }
  return path;
}

fs::path GameData::GetLogsPath() {
  fs::path path = fs::current_path() / "logs";
  if (!fs::exists(path)) {
    fs::create_directories(path);
  }
  return path;
}

fs::path GameData::GetSavesPath() {
  fs::path path = GetGlobalPath() / "saves";
  if (!fs::exists(path)) {
    fs::create_directories(path);
  }
  return path;
}

fs::path GameData::GetConfigPath() {
  fs::path path = GetGlobalPath() / "config";
  if (!fs::exists(path)) {
    fs::create_directories(path);
  }
  return path;
}

} // namespace farmomatica
