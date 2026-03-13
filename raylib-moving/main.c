#include <raylib.h>
#include <stdio.h>

int main() {
  const int screen_height = 450;
  const int screen_width = 800;
  const int circle_radius = 50;
  const float move_speed = 2.0;
  int score = 0;

  InitWindow(screen_width, screen_height, "This is some title");

  SetTargetFPS(144);

  Vector2 ball_pos = {.x = 90.0f, .y = 90.0f};
  Vector2 target_pos = {.x = 200.0f, .y = 200.0f};
  SetRandomSeed(24);

  while (!WindowShouldClose()) {
    float dt = GetFrameTime() * 100;

    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
      ball_pos.x += move_speed * dt;
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
      ball_pos.x -= move_speed * dt;
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
      ball_pos.y += move_speed * dt;
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
      ball_pos.y -= move_speed * dt;

    if (ball_pos.y < circle_radius)
      ball_pos.y = circle_radius;
    if (ball_pos.x < circle_radius)
      ball_pos.x = circle_radius;
    if (ball_pos.x > screen_width - circle_radius)
      ball_pos.x = screen_width - circle_radius;
    if (ball_pos.y > screen_height - circle_radius)
      ball_pos.y = screen_height - circle_radius;

    if (CheckCollisionCircles(ball_pos, circle_radius, target_pos,
                              circle_radius)) {
      score += 1;
      target_pos.x =
          GetRandomValue(circle_radius, screen_width - circle_radius);
      target_pos.y =
          GetRandomValue(circle_radius, screen_height - circle_radius);
    }

    BeginDrawing();

    ClearBackground(DARKGRAY);

    DrawCircleV(ball_pos, circle_radius, GOLD);
    DrawCircleV(target_pos, circle_radius, GREEN);

    DrawText(TextFormat("Score is: %d", score), 12, 12, 24, WHITE);
    EndDrawing();
  }

  return 0;
}
