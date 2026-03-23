#pragma once

#include <array>
#include <string_view>

namespace farmomatica {
namespace Settings {
namespace Global {
inline constexpr std::string_view NAME = "Farmomatica";
inline constexpr std::array<std::string_view, 1> SUPPORTED_TEXTURE_EXTENSIONS = {
    ".png"};
} // namespace Global
} // namespace Settings
} // namespace farmomatica
