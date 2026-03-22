#include <filesystem>

class GameData {
public:
  static std::filesystem::path GetTexturesPath();
  static std::filesystem::path GetShadersPath();
  static std::filesystem::path GetLogsPath();
  static std::filesystem::path GetSavesPath();
  static std::filesystem::path GetConfigPath();
};
