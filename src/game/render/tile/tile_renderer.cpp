#include "game/render/tile/tile_renderer.h"
#include "game/assets/texture_loader.h"

namespace farmomatica {

void RenderTile(const std::string &name, Vector3 pos) {
  const Texture2D *texture = texture_loader::GetTexture(name);

  if (texture == nullptr) {
    return;
  }

  DrawTexture(*texture, pos.x, pos.y, WHITE);
}

} // namespace farmomatica
