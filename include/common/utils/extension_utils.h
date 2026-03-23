#pragma once

#include <algorithm>
#include <string_view>

#include "common/settings/global_settings.h"

namespace farmomatica::utils {

inline constexpr bool isTextureExtensionSupported(std::string_view extension) noexcept {
  return std::find(config::TEXTURE_EXTENSIONS.begin(),
                   config::TEXTURE_EXTENSIONS.end(),
                   extension) != config::TEXTURE_EXTENSIONS.end();
}

} // namespace farmomatica::utils
