#include "game/assets/texture_loader.h"

#include <unordered_map>

#include "common/logger/log.h"
#include "common/utils/extension_utils.h"

namespace fs = std::filesystem;

namespace farmomatica {
namespace TextureLoader {
static std::unordered_map<std::string, Texture2D> tiles;

void LoadTextures(const fs::path &path) {
  if (!fs::exists(path)) {
    return;
  }

  for (const fs::directory_entry &entry : fs::directory_iterator(path)) {
    if (entry.is_regular_file()) {
      if (Utils::isTextureExtensionSupported(
              entry.path().extension().string())) {
        Texture2D texture = LoadTexture(entry.path().c_str());

        fs::path relative =
            fs::relative(entry.path(), path).replace_extension("");

        tiles[relative.string()] = texture;

        LOG_DEBUG("Texture loaded successfully: {}", relative.string());
      } else {
        LOG_WARN("Unsupported texture extension: {}", entry.path().string());
      }
    }
  }
}

void UnloadTexture(const std::string &identifier) {
  auto it = tiles.find(identifier);

  if (it != tiles.end()) {
    UnloadTexture(it->second);
    tiles.erase(it);
  } else {
    LOG_WARN("Texture not found: {}", identifier);
  }
}

Texture2D *GetTexture(const std::string &identifier) {
  auto it = tiles.find(identifier);

  if (it != tiles.end()) {
    return &it->second;
  }

  LOG_WARN("Texture not found: {}", identifier);
  return nullptr;
}
} // namespace TextureLoader
} // namespace farmomatica