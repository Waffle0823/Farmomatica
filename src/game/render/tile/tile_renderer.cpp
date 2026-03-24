#include "game/render/tile/tile_renderer.h"
#include "game/assets/shader_loader.h"
#include "game/assets/texture_loader.h"

namespace farmomatica {

namespace {

}  // namespace

void RenderTile(std::string_view name, Vector3 pos) noexcept {
    auto textureOpt = TextureLoader::GetInstance().GetTexture(name);
    if (!textureOpt.has_value()) {
        return;
    }

    auto shaderOpt = ShaderLoader::GetInstance().GetShader("farmomatica/tile_shader");
    if (!shaderOpt.has_value()) {
        DrawTexture(textureOpt->get(), static_cast<int>(pos.x), static_cast<int>(pos.y), WHITE);
        return;
    }

    Shader& shader = shaderOpt->get();
    const Texture2D& texture = textureOpt->get();

    const float tilePos[3] = {pos.x, pos.y, pos.z};
    const float tileDim[2] = {static_cast<float>(texture.width), static_cast<float>(texture.height)};
    const float screenCenter[2] = {static_cast<float>(GetScreenWidth()) / 2.0f,
                                   static_cast<float>(GetScreenHeight()) / 2.0f};

    int locTilePos = GetShaderLocation(shader, "tilePos");
    int locTileDim = GetShaderLocation(shader, "tileDim");
    int locScreenCenter = GetShaderLocation(shader, "screenCenter");

    BeginShaderMode(shader);
    SetShaderValue(shader, locTilePos, tilePos, SHADER_UNIFORM_VEC3);
    SetShaderValue(shader, locTileDim, tileDim, SHADER_UNIFORM_VEC2);
    SetShaderValue(shader, locScreenCenter, screenCenter, SHADER_UNIFORM_VEC2);
    DrawTexture(texture, 0, 0, WHITE);
    EndShaderMode();
}

}  // namespace farmomatica
