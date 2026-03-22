#pragma once

#include <filesystem>
#include <raylib.h>
#include <string>
#include <unordered_map>

class TileLoader {
public:
  static bool LoadTiles(const std::filesystem::path &path);
  static Texture2D GetTile(const std::string &path);

private:
  static std::unordered_map<std::string, Texture2D> tiles;
};
