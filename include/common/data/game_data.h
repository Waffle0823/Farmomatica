#pragma once

#include <filesystem>

namespace farmomatica {

class GameData {
public:
  /**
   * @brief Gets the path to the textures directory.
   * @return The filesystem path to the textures directory.
   * @throws std::filesystem::filesystem_error If the directory cannot be created or accessed.
   */
  static std::filesystem::path GetTexturesPath();

  /**
   * @brief Gets the path to the shaders directory.
   * @return The filesystem path to the shaders directory.
   * @throws std::filesystem::filesystem_error If the directory cannot be created or accessed.
   */
  static std::filesystem::path GetShadersPath();

  /**
   * @brief Gets the path to the logs directory.
   * @return The filesystem path to the logs directory.
   * @throws std::filesystem::filesystem_error If the directory cannot be created or accessed.
   */
  static std::filesystem::path GetLogsPath();

  /**
   * @brief Gets the path to the saves directory.
   * @return The filesystem path to the saves directory.
   * @throws std::filesystem::filesystem_error If the directory cannot be created or accessed.
   */
  static std::filesystem::path GetSavesPath();

  /**
   * @brief Gets the path to the config directory.
   * @return The filesystem path to the config directory.
   * @throws std::filesystem::filesystem_error If the directory cannot be created or accessed.
   */
  static std::filesystem::path GetConfigPath();
};

} // namespace farmomatica
