#include "game/assets/shader_loader.h"
#include <iostream>

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
    if (!fs::exists(path) || !fs::is_directory(path)) {
        LOG_WARN("Shader path does not exist or is not a directory: {}", path.string());
        return;
    }

    for (const auto& entry : fs::recursive_directory_iterator(path)) {
        if (!entry.is_regular_file()) continue;

        std::string ext = entry.path().extension().string();

        if (utils::IsShaderExtensionSupported(ext)) {
            char* shaderSource = LoadFileText(entry.path().c_str());
            if (shaderSource == nullptr) {
                LOG_ERROR("Failed to read shader file: {}", entry.path().string());
                continue;
            }

            Shader shader = LoadShaderFromMemory(nullptr, shaderSource);

            UnloadFileText(shaderSource);

            if (shader.id == 0) {
                LOG_ERROR("Failed to compile pipeline: {}", entry.path().string());
                continue;
            }

            fs::path relative = fs::relative(entry.path(), path);
            relative.replace_extension("");

            std::cout << "Loading shader: " << relative.string() << std::endl;

            shaders_[relative.string()] = shader;

            LOG_DEBUG("Shader (pipeline) loaded successfully: {}", relative.string());
        } else {
            LOG_WARN("Unsupported shader extension: {}", entry.path().string());
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
