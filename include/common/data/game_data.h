#pragma once

#include <filesystem>

namespace farmomatica::paths {

/**
 * @brief Gets the path to the textures directory.
 * @return The filesystem path to the textures directory.
 * @throws std::filesystem::filesystem_error If the directory cannot be created or accessed.
 */
std::filesystem::path getTexturesPath();

/**
 * @brief Gets the path to the shaders directory.
 * @return The filesystem path to the shaders directory.
 * @throws std::filesystem::filesystem_error If the directory cannot be created or accessed.
 */
std::filesystem::path getShadersPath();

/**
 * @brief Gets the path to the logs directory.
 * @return The filesystem path to the logs directory.
 * @throws std::filesystem::filesystem_error If the directory cannot be created or accessed.
 */
std::filesystem::path getLogsPath();

/**
 * @brief Gets the path to the saves directory.
 * @return The filesystem path to the saves directory.
 * @throws std::filesystem::filesystem_error If the directory cannot be created or accessed.
 */
std::filesystem::path getSavesPath();

/**
 * @brief Gets the path to the config directory.
 * @return The filesystem path to the config directory.
 * @throws std::filesystem::filesystem_error If the directory cannot be created or accessed.
 */
std::filesystem::path getConfigPath();

} // namespace farmomatica::paths
