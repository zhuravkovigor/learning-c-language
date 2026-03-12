#include <raylib.h>

int main() {
  const int screen_width = 800;
  const int screen_height = 450;
  const int circle_radius = 50;
  const int cube_size = 80;

  InitWindow(screen_width, screen_height, "This is some title");

  SetTargetFPS(144);

  while (!WindowShouldClose())
  {
    BeginDrawing();
      ClearBackground(DARKGRAY);
      DrawCircle(screen_width / 2, screen_height / 2, circle_radius, GOLD);
      DrawRectangle(screen_width / 2 - cube_size / 2, screen_height / 2 + (cube_size + (circle_radius / 2)) / 2, cube_size, cube_size, YELLOW);
    EndDrawing();
  }
  

  return 0;
}