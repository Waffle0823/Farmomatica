#pragma once

#include <array>
#include <string_view>

namespace farmomatica {
namespace settings {
namespace global {

namespace application {
inline constexpr std::string_view NAME = "Farmomatica";
} // namespace application

namespace assets {
namespace textures {
inline constexpr std::array<std::string_view, 1> SUPPORTED_EXTENSIONS = {
    ".png"};
inline constexpr int NULL_TEXTURE_WIDTH = 32;
inline constexpr int NULL_TEXTURE_HEIGHT = 32;
} // namespace textures
} // namespace assets
} // namespace global
} // namespace settings
} // namespace farmomatica
