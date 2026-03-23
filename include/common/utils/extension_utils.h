#pragma once

#include <algorithm>
#include <array>
#include <string_view>

#include "common/settings/global_settings.h"

namespace farmomatica {
namespace Utils {
inline constexpr bool isTextureExtensionSupported(std::string_view extension) {
  return std::find(Settings::Global::SUPPORTED_TEXTURE_EXTENSIONS.begin(),
                   Settings::Global::SUPPORTED_TEXTURE_EXTENSIONS.end(),
                   extension) !=
         Settings::Global::SUPPORTED_TEXTURE_EXTENSIONS.end();
}
} // namespace Utils
} // namespace farmomatica
