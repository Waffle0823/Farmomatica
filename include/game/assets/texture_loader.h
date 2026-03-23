#include <filesystem>
#include <raylib.h>
#include <string>

namespace farmomatica {
namespace texture_loader {
/**
 * @brief Loads all textures from the specified directory path.
 * @param path The filesystem path to the directory containing textures.
 * @throws std::filesystem::filesystem_error If the directory cannot be accessed
 * or read.
 */
void LoadTextures(const std::filesystem::path &path);

/**
 * @brief Unloads a texture by its identifier.
 * @param identifier The string identifier of the texture to unload.
 */
void UnloadTexture(const std::string &identifier);

/**
 * @brief Retrieves a texture by its identifier.
 * @param identifier The string identifier of the texture to retrieve.
 * @return The requested Texture2D, or an null pointer if the texture does
 * not exist.
 */
Texture2D *GetTexture(const std::string &identifier);
} // namespace texture_loader
} // namespace farmomatica