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
    if (!fs::exists(path) || !fs::is_directory(path)) {
        LOG_WARN("Shader path does not exist or is not a directory: {}", path.string());
        return;
    }

    std::unordered_map<std::string, std::pair<fs::path, fs::path>> shaderPairs;

    for (const auto& entry : fs::recursive_directory_iterator(path)) {
        if (!entry.is_regular_file()) continue;

        std::string ext = entry.path().extension().string();

        if (utils::IsShaderExtensionSupported(ext)) {
            fs::path relative = fs::relative(entry.path(), path);
            fs::path baseName = relative;
            baseName.replace_extension("");
            std::string baseNameStr = baseName.string();

            if (ext == ".vs") {
                shaderPairs[baseNameStr].first = entry.path();
            } else if (ext == ".fs") {
                shaderPairs[baseNameStr].second = entry.path();
            }
        }
    }

    for (const auto& [baseName, paths] : shaderPairs) {
        const auto& [vsPath, fsPath] = paths;

        char* vsSource = nullptr;
        char* fsSource = nullptr;

        if (!vsPath.empty()) {
            vsSource = LoadFileText(vsPath.c_str());
            if (vsSource == nullptr) {
                LOG_ERROR("Failed to read vertex shader file: {}", vsPath.string());
            }
        }

        if (!fsPath.empty()) {
            fsSource = LoadFileText(fsPath.c_str());
            if (fsSource == nullptr) {
                LOG_ERROR("Failed to read fragment shader file: {}", fsPath.string());
            }
        }

        if (vsSource == nullptr && fsSource == nullptr) {
            LOG_ERROR("Failed to load both shaders for: {}", baseName);
            continue;
        }

        Shader shader = LoadShaderFromMemory(vsSource, fsSource);

        if (vsSource != nullptr) UnloadFileText(vsSource);
        if (fsSource != nullptr) UnloadFileText(fsSource);

        if (shader.id == 0) {
            LOG_ERROR("Failed to compile shader: {}", baseName);
            continue;
        }

        shaders_[baseName] = shader;

        LOG_DEBUG("Shader loaded successfully: {}", baseName);
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
