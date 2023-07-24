#include "raylib.h"
int main(){
  InitWindow(800, 450, "raylib [core] example - basic window");

  int x = 190, y = 200;

  while (!WindowShouldClose()){
    if (IsKeyDown(KEY_LEFT)) x-=.1f;
    if (IsKeyDown(KEY_RIGHT)) x+=.1f;
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Congrats! You created your first window!", x, 200, 20, RED);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}

