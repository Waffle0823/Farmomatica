#pragma once

#include <filesystem>
#include <optional>
#include <functional>
#include <raylib.h>
#include <string>
#include <string_view>
#include <unordered_map>

namespace farmomatica {

class TextureLoader {
public:
  static TextureLoader &getInstance() noexcept;

  TextureLoader(const TextureLoader &) = delete;
  TextureLoader &operator=(const TextureLoader &) = delete;
  TextureLoader(TextureLoader &&) = delete;
  TextureLoader &operator=(TextureLoader &&) = delete;

  /**
   * @brief Loads all textures from the specified directory path.
   * @param path The filesystem path to the directory containing textures.
   * @throws std::filesystem::filesystem_error If the directory cannot be accessed
   * or read.
   */
  void loadTextures(const std::filesystem::path &path);

  /**
   * @brief Unloads a texture by its identifier.
   * @param identifier The string identifier of the texture to unload.
   */
  void unloadTexture(std::string_view identifier) noexcept;

  /**
   * @brief Retrieves a texture by its identifier.
   * @param identifier The string identifier of the texture to retrieve.
   * @return Optional reference to the Texture2D if found, std::nullopt otherwise.
   */
  std::optional<std::reference_wrapper<Texture2D>> getTexture(std::string_view identifier) noexcept;

  /**
   * @brief Unloads all textures and cleans up resources.
   */
  void unloadAll() noexcept;

private:
  TextureLoader() = default;
  ~TextureLoader() noexcept;

  std::unordered_map<std::string, Texture2D> tiles_;
};

} // namespace farmomatica