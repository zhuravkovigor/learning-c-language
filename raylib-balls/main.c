#include <raylib.h>
#include <stdio.h>

typedef enum { MENU, GAME, GAME_OVER } GameStates;
typedef enum {
  LEFT,
  RIGHT,
} EnemySides;

int main() {
  const int window_width = 800;
  const int window_height = 450;
  const int circle_radius = 50;
  const int coin_radius = 20;
  const float move_speed = 5.0f;
  const int enemy_width = 100;
  const int enemy_height = 20;
  float enemy_speed_x = 2.f;
  const int game_font_size = 24;
  const char text_for_menu[] = "To Start game enter Enter";
  const char text_for_gameover[] = "Game Over, press space to go menu";
  float timer = 5.0f;

  Vector2 player_position = {.x = (float)window_width / 2 - circle_radius,
                             .y = (float)window_height / 2 - circle_radius};
  Vector2 enemy_position = {.x = 0, .y = (float)window_height / 2};
  Vector2 coin_position = {
      .x = GetRandomValue(coin_radius, window_width - coin_radius),
      .y = GetRandomValue(coin_radius, window_height - coin_radius)};
  GameStates current_game_state = MENU;
  EnemySides enemy_side_move = LEFT;
  int score = 0;

  InitWindow(window_width, window_height, "This is a title for the game");
  SetTargetFPS(144);

  while (!WindowShouldClose()) {
    float dt = (GetFrameTime() * 100);

    if (current_game_state == GAME) {
      // Check if game is over
      Rectangle enemy_rectangle = {.x = enemy_position.x,
                                   .y = enemy_position.y,
                                   .width = enemy_width,
                                   .height = enemy_height};

      if (CheckCollisionCircleRec(player_position, circle_radius,
                                  enemy_rectangle)) {
        current_game_state = GAME_OVER;
      }

      // coin collision
      if (CheckCollisionCircles(coin_position, coin_radius, player_position,
                                circle_radius)) {
        score += 1;
        timer += 1.0f;
        coin_position.x =
            GetRandomValue(coin_radius, window_width - coin_radius);
        coin_position.y =
            GetRandomValue(coin_radius, window_height - coin_radius);

        // Increase enemy speed
        enemy_speed_x *= 1.1;
      }

      if (enemy_position.x < 0) {
        enemy_side_move = LEFT;
      } else if (enemy_position.x > window_width - enemy_width) {
        enemy_side_move = RIGHT;
      }

      // moving enemy
      if (enemy_side_move == LEFT) {
        enemy_position.x += enemy_speed_x * dt;
      } else if (enemy_side_move == RIGHT) {
        enemy_position.x -= enemy_speed_x * dt;
      }

      // Player movements
      if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        player_position.x += move_speed * dt;
      }

      if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        player_position.x -= move_speed * dt;
      }

      if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
        player_position.y -= move_speed * dt;
      }

      if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
        player_position.y += move_speed * dt;
      }

      if (timer > 0) {
        timer -= GetFrameTime();
      } else {
        current_game_state = GAME_OVER;
      }
    }

    // Working with a game state
    if (current_game_state == MENU) {
      if (IsKeyPressed(KEY_ENTER)) {
        current_game_state = GAME;
      }
    }

    if (current_game_state == GAME_OVER) {
      if (IsKeyPressed(KEY_SPACE)) {
        current_game_state = MENU;
        score = 0;
        player_position.x = (float)window_width / 2 - circle_radius;
        player_position.y = (float)window_height / 2 - circle_radius;
        timer = 3;
        enemy_speed_x = 2.0f;
        enemy_position.x = 0, enemy_position.y = (float)window_height / 2;
      }
    }

    BeginDrawing();
    ClearBackground(BLACK);

    if (current_game_state == MENU) {
      DrawText(text_for_menu,
               window_width / 2 -
                   MeasureText(text_for_menu, game_font_size) / 2,
               window_height / 2, game_font_size, WHITE);
    }

    if (current_game_state == GAME) {
      // Drawing coin
      DrawCircleV(coin_position, coin_radius, GOLD);

      // Player
      DrawCircleV(player_position, circle_radius, WHITE);

      // Drawing enemy
      DrawRectangle(enemy_position.x, enemy_position.y, enemy_width,
                    enemy_height, RED);

      // Draw timer
      DrawText(TextFormat("Timer: %.0f", timer),
               window_width - 15 -
                   MeasureText(TextFormat("Timer: %.0f", timer), 16),
               12, 16, WHITE);

      // Draw score
      DrawText(TextFormat("Score %d", score), 12, 12, 16, WHITE);
    }

    if (current_game_state == GAME_OVER) {
      DrawText(text_for_gameover,
               window_width / 2 -
                   MeasureText(text_for_gameover, game_font_size) / 2,
               window_height / 2 - 30, game_font_size, WHITE);
      DrawText(TextFormat("You'r score is %d", score),
               window_width / 2 -
                   MeasureText(TextFormat("You'r score is %d", score),
                               game_font_size) /
                       2,
               window_height / 2 + 20, game_font_size, WHITE);
    }

    EndDrawing();
  }

  return 0;
}
