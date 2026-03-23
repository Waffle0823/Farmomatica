#pragma once

#include <algorithm>
#include <array>
#include <string_view>

#include "common/settings/global_settings.h"

namespace farmomatica {
namespace utils {
inline constexpr bool isTextureExtensionSupported(std::string_view extension) {
  return std::find(settings::global::assets::textures::SUPPORTED_EXTENSIONS.begin(),
                   settings::global::assets::textures::SUPPORTED_EXTENSIONS.end(),
                   extension) !=
         settings::global::assets::textures::SUPPORTED_EXTENSIONS.end();
}
} // namespace utils
} // namespace farmomatica
