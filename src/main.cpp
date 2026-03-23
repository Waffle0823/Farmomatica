#include "common/logger/log.h"
#include <raylib.h>

using farmomatica::Log;

constexpr int windowWidth = 800;
constexpr int windowHeight = 600;

int main(int, char **) {
  try {
    Log::Init();
    LOG_INFO("Logger Initialized");

    InitWindow(windowWidth, windowHeight, "Farmomatica");
    LOG_INFO("Window Initialized");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
      BeginDrawing();
      ClearBackground(RAYWHITE);
      DrawText("Hello raylib!", 190, 200, 20, DARKGRAY);
      EndDrawing();
    }

    CloseWindow();
    return 0;
  } catch (const std::exception &e) {
    LOG_CRITICAL("Unhandled exception: {}", e.what());
    CloseWindow();
    return 1;
  } catch (...) {
    LOG_CRITICAL("Unknown exception occurred");
    CloseWindow();
    return 1;
  }
}
