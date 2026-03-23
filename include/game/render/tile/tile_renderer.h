#pragma once

#include <raylib.h>
#include <string>

namespace farmomatica {

/**
 * @brief Renders a tile at the specified position.
 * @param name The string identifier of the texture to render.
 * @param pos The 3D position where the tile should be rendered.
 */
void RenderTile(const std::string &name, Vector3 pos);

} // namespace farmomatica
