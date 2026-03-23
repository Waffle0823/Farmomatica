#include "game/assets/texture_loader.h"

#include "common/logger/log.h"
#include "common/utils/extension_utils.h"

namespace fs = std::filesystem;

namespace farmomatica {

TextureLoader &TextureLoader::getInstance() noexcept {
  static TextureLoader instance;
  return instance;
}

TextureLoader::~TextureLoader() noexcept {
  unloadAll();
}

void TextureLoader::loadTextures(const fs::path &path) {
  if (!fs::exists(path)) {
    return;
  }

  for (const fs::directory_entry &entry : fs::directory_iterator(path)) {
    if (entry.is_regular_file()) {
      if (utils::isTextureExtensionSupported(
              entry.path().extension().string())) {
        Texture2D texture = LoadTexture(entry.path().c_str());

        fs::path relative =
            fs::relative(entry.path(), path).replace_extension("");

        tiles_[relative.string()] = texture;

        LOG_DEBUG("Texture loaded successfully: {}", relative.string());
      } else {
        LOG_WARN("Unsupported texture extension: {}", entry.path().string());
      }
    }
  }
}

void TextureLoader::unloadTexture(std::string_view identifier) noexcept {
  auto it = tiles_.find(std::string(identifier));

  if (it != tiles_.end()) {
    UnloadTexture(it->second);
    tiles_.erase(it);
  } else {
    LOG_WARN("Texture not found: {}", identifier);
  }
}

std::optional<std::reference_wrapper<Texture2D>> TextureLoader::getTexture(std::string_view identifier) noexcept {
  auto it = tiles_.find(std::string(identifier));

  if (it != tiles_.end()) {
    return std::ref(it->second);
  }

  LOG_WARN("Texture not found: {}", identifier);
  return std::nullopt;
}

void TextureLoader::unloadAll() noexcept {
  for (auto &[identifier, texture] : tiles_) {
    UnloadTexture(texture);
  }
  tiles_.clear();
  LOG_DEBUG("All textures unloaded");
}

} // namespace farmomatica