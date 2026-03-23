#include "game/render/tile/tile_renderer.h"
#include "game/assets/texture_loader.h"

namespace farmomatica {

void RenderTile(std::string_view name, Vector3 pos) noexcept {
  auto textureOpt = TextureLoader::getInstance().getTexture(name);

  if (!textureOpt.has_value()) {
    return;
  }

  DrawTexture(textureOpt->get(), pos.x, pos.y, WHITE);
}

} // namespace farmomatica
