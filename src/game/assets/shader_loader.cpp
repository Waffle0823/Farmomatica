#include "game/assets/shader_loader.h"

#include "common/logger/log.h"
#include "common/utils/extension_utils.h"

namespace fs = std::filesystem;

namespace farmomatica {

ShaderLoader& ShaderLoader::GetInstance() noexcept {
    static ShaderLoader instance;
    return instance;
}

ShaderLoader::~ShaderLoader() noexcept {
    UnloadAll();
}

void ShaderLoader::LoadShaders(const fs::path& path) {
    if (!fs::exists(path)) {
        return;
    }

    for (const fs::directory_entry& entry : fs::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            if (utils::IsShaderExtensionSupported(
                    entry.path().extension().string())) {
                Shader shader = LoadShaderSingleSource(entry.path().c_str());

                fs::path relative =
                    fs::relative(entry.path(), path).replace_extension("");

                shaders_[relative.string()] = shader;

                LOG_DEBUG("Shader loaded successfully: {}", relative.string());
            } else {
                LOG_WARN("Unsupported shader extension: {}", entry.path().string());
            }
        }
    }
}

void ShaderLoader::UnloadShader(std::string_view identifier) noexcept {
    auto it = shaders_.find(std::string(identifier));

    if (it != shaders_.end()) {
        ::UnloadShader(it->second);
        shaders_.erase(it);
    } else {
        LOG_WARN("Shader not found: {}", identifier);
    }
}

std::optional<std::reference_wrapper<Shader>> ShaderLoader::GetShader(std::string_view identifier) noexcept {
    auto it = shaders_.find(std::string(identifier));

    if (it != shaders_.end()) {
        return std::ref(it->second);
    }

    LOG_WARN("Shader not found: {}", identifier);
    return std::nullopt;
}

void ShaderLoader::UnloadAll() noexcept {
    for (auto& [identifier, shader] : shaders_) {
        ::UnloadShader(shader);
    }
    shaders_.clear();
    LOG_DEBUG("All shaders unloaded");
}

}  // namespace farmomatica
