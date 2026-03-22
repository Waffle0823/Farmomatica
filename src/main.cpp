#include "common/logger/log.h"
#include <raylib.h>

constexpr int windowWidth = 800;
constexpr int windowHeight = 600;

int main(int, char **) {
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
}
