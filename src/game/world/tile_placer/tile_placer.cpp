#include <raylib.h>
#include <string>

#include "game/assets/tile/tile_loader.h"
#include "game/world/tile_placer/tile_placer.h"

void TilePlacer::PlaceTile(const std::string &name, const int x, const int y,
                           const int z) {
  const Texture2D texture = TileLoader::GetTile(name);

  const int tileWidth = texture.width;
  const int tileHeight = texture.height;

  const int isoX = (x - y) * (tileWidth / 2);
  const int isoY = (x + y) * (tileHeight / 4) - z * (tileHeight / 2);

  const int screenCenterX = GetScreenWidth() / 2;
  const int screenCenterY = GetScreenHeight() / 2;

  const int screenX = isoX + screenCenterX;
  const int screenY = isoY + screenCenterY;

  DrawTexture(texture, screenX, screenY, WHITE);
}
