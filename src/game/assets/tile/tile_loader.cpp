#include <filesystem>
#include <raylib.h>
#include <string>

#include "common/logger/log.h"
#include "game/assets/tile/tile_loader.h"

namespace fs = std::filesystem;

std::unordered_map<std::string, Texture2D> TileLoader::tiles;

bool TileLoader::LoadTiles(const std::filesystem::path &path) {
  try {
    for (const auto &entry : fs::directory_iterator(path)) {
      if (fs::is_regular_file(entry.status()) &&
          entry.path().extension() == ".png") {
        fs::path relative =
            fs::relative(entry.path(), path).replace_extension("");

        tiles[relative.string()] = LoadTexture(entry.path().c_str());
        LOG_DEBUG("Texture loaded successfully: {}", relative.string());
      } else {
        LOG_WARN("Unsupported texture: {}", entry.path().string());
        return false;
      }
    }
  } catch (const fs::filesystem_error &e) {
    LOG_ERROR("Failed to load texture: {}", e.what());
    return false;
  }

  return true;
}

Texture2D TileLoader::GetTile(const std::string &path) {
  auto it = tiles.find(path);
  if (it != tiles.end()) {
    return it->second;
  }

  LOG_ERROR("Tile not found: {}", path);
  return Texture2D{};
}
