#include "common/setting/global_settings.h"
#include "common/logger/log.h"

std::unordered_map<std::string, std::any> GlobalSettings::settings;

template <typename T> void GlobalSettings::Set(const std::string &key, const T value) {
  settings[key] = value;
}

template <typename T> T GlobalSettings::Get(const std::string &key) {
  if (settings.find(key) == settings.end()) {
    LOG_WARN("Key not found in global settings: {}", key);
    return T();
  }
  return std::any_cast<T>(settings[key]);
}

bool GlobalSettings::Has(const std::string &key) {
  return settings.find(key) != settings.end();
}
