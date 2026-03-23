#pragma once

#include <array>
#include <string_view>

namespace farmomatica {
namespace Settings {
namespace Global {

namespace Application {
inline constexpr std::string_view NAME = "Farmomatica";
} // namespace Application

namespace Assets {
namespace Textures {
inline constexpr std::array<std::string_view, 1> SUPPORTED_EXTENSIONS = {
    ".png"};
inline constexpr int NULL_TEXTURE_WIDTH = 32;
inline constexpr int NULL_TEXTURE_HEIGHT = 32;
} // namespace Textures
} // namespace Assets
} // namespace Global
} // namespace Settings
} // namespace farmomatica
