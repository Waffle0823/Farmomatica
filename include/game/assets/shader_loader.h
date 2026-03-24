#pragma once

#include <filesystem>
#include <functional>
#include <optional>
#include <raygpu.h>
#include <string>
#include <string_view>
#include <unordered_map>

namespace farmomatica {

class ShaderLoader {
public:
    static ShaderLoader& GetInstance() noexcept;

    ShaderLoader(const ShaderLoader&) = delete;
    ShaderLoader& operator=(const ShaderLoader&) = delete;
    ShaderLoader(ShaderLoader&&) = delete;
    ShaderLoader& operator=(ShaderLoader&&) = delete;

    /**
     * @brief Loads all shaders from the specified directory path.
     * @param path The filesystem path to the directory containing shaders.
     * @throws std::filesystem::filesystem_error If the directory cannot be accessed
     * or read.
     */
    void LoadShaders(const std::filesystem::path& path);

    /**
     * @brief Unloads a shader by its identifier.
     * @param identifier The string identifier of the shader to unload.
     */
    void UnloadShader(std::string_view identifier) noexcept;

    /**
     * @brief Retrieves a shader pipeline by its identifier.
     * @param identifier The string identifier of the shader to retrieve.
     * @return Optional reference to the Shader if found, std::nullopt otherwise.
     */
    std::optional<std::reference_wrapper<Shader>> GetShader(std::string_view identifier) noexcept;

    /**
     * @brief Unloads all shaders and cleans up resources.
     */
    void UnloadAll() noexcept;

private:
    ShaderLoader() = default;
    ~ShaderLoader() noexcept;

    std::unordered_map<std::string, Shader> shaders_;
};

}  // namespace farmomatica
