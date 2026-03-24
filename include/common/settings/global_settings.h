#pragma once

#include <array>
#include <string_view>

namespace farmomatica::config {

inline constexpr std::string_view APPLICATION_NAME = "Farmomatica";

inline constexpr std::string_view LOG_FILE_NAME = "latest.log";

inline constexpr std::array<std::string_view, 1> TEXTURE_EXTENSIONS = {".png"};
inline constexpr int NULL_TEXTURE_WIDTH = 32;
inline constexpr int NULL_TEXTURE_HEIGHT = 32;

}  // namespace farmomatica::config
