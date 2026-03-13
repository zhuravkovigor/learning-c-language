#include <raylib.h>

int main() {
  const int screen_height = 450;
  const int screen_width = 800;
  const int circle_radius = 50;

  InitWindow(screen_width, screen_height, "This is some title");

  SetTargetFPS(144);
  float circle_x = 90.0f;
  float circle_y = 90.0f;
  float move_speed = 2.0;

  while (!WindowShouldClose())
  {
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) circle_x += move_speed;
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) circle_x -= move_speed;
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) circle_y += move_speed;
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) circle_y -= move_speed;

    if (circle_y < circle_radius) circle_y = circle_radius;
    if (circle_x < circle_radius) circle_x = circle_radius;
    if (circle_x > screen_width - circle_radius) circle_x = screen_width - circle_radius;
    if (circle_y > screen_height - circle_radius) circle_y = screen_height - circle_radius;

    BeginDrawing();
      ClearBackground(DARKGRAY);
      DrawCircle(circle_x, circle_y, circle_radius, GOLD);
    EndDrawing();
  }
  

  return 0;
}