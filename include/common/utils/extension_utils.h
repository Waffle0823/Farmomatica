#pragma once

#include <algorithm>
#include <string_view>

#include "common/settings/global_settings.h"

namespace farmomatica::utils {

constexpr bool IsTextureExtensionSupported(std::string_view extension) noexcept {
    return std::ranges::find(config::TEXTURE_EXTENSIONS, extension) !=
           config::TEXTURE_EXTENSIONS.end();
}

}  // namespace farmomatica::utils
