#include <raylib.h>

int main(int, char **) {
  constexpr int windowWidth = 800;
  constexpr int windowHeight = 600;

  InitWindow(windowWidth, windowHeight, "Farmomatica");

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
