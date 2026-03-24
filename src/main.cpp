#include <raylib.h>
#include <rlgl.h>

#include "common/data/game_data.h"
#include "common/logger/log.h"
#include "game/assets/shader_loader.h"
#include "game/assets/texture_loader.h"

using farmomatica::Log;

constexpr int windowWidth = 800;
constexpr int windowHeight = 600;

int main(int, char**) {
    try {
        Log::Init();
        LOG_INFO("Logger Initialized");

        InitWindow(windowWidth, windowHeight, "Farmomatica");
        LOG_INFO("Window Initialized");

        SetTargetFPS(60);

        farmomatica::ShaderLoader::GetInstance().LoadShaders(farmomatica::paths::GetShadersPath());
        farmomatica::TextureLoader::GetInstance().LoadTextures(farmomatica::paths::GetTexturesPath());
        LOG_INFO("Textures loaded");

        while (!WindowShouldClose()) {
            BeginDrawing();
            ClearBackground(RAYWHITE);

            rlEnableDepthTest();

            // TODO: Render logic

            rlDisableDepthTest();

            DrawText("Testing Tile Renderer", 190, 200, 20, DARKGRAY);
            DrawFPS(10, 10);
            EndDrawing();
        }

        farmomatica::TextureLoader::GetInstance().UnloadAll();
        farmomatica::ShaderLoader::GetInstance().UnloadAll();

        CloseWindow();
        return 0;
    } catch (const std::exception& e) {
        LOG_CRITICAL("Unhandled exception: {}", e.what());
        CloseWindow();
        return 1;
    } catch (...) {
        LOG_CRITICAL("Unknown exception occurred");
        CloseWindow();
        return 1;
    }
}
