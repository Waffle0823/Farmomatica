#include "game/render/tile/tile_renderer.h"
#include "game/assets/texture_loader.h"

namespace farmomatica {

void RenderTile(std::string_view name, Vector3 pos) noexcept {
    auto textureOpt = TextureLoader::GetInstance().GetTexture(name);

    if (!textureOpt.has_value()) {
        return;
    }

    DrawTexture(textureOpt->get(), static_cast<int>(pos.x), static_cast<int>(pos.y), WHITE);
}

}  // namespace farmomatica
