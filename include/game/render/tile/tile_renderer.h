#pragma once

#include <raygpu.h>
#include <string_view>

namespace farmomatica {

/**
 * @brief Renders a tile at the specified position.
 * @param name The string identifier of the texture to render.
 * @param pos The 3D position where the tile should be rendered.
 */
void RenderTile(std::string_view name, Vector3 pos) noexcept;

} // namespace farmomatica
