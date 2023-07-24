
#include "raylib.h"
#include <vector>
#include <iostream>


Color TurnColors[] = {
    DARKGRAY, RED, GREEN
};

enum Turn {
    FREE, LEFT, RIGHT
} turn;

struct Element {
    Rectangle pos;
    Turn turn;
    bool done;
};

// board elements
const float ROUNDEDNESS = 0.4f;
const int SIZE = 80;
const int PADDING = 10;
const float START_X = 50.f, START_Y = 50.f;

// size
const int GRID_SIZE = 3;
Element board[GRID_SIZE][GRID_SIZE];

// globals
bool GAME_OVER = false;
Turn WINNER = LEFT;

bool check (Turn turn, int i, int j) {
    if (i >= GRID_SIZE || i < 0) return false;
    if (j >= GRID_SIZE || j < 0) return false;
    return board[i][j].turn == turn;
}
// generic win checker for all grid sizes
void checkWinner(Turn turn, int i, int j) {
    if ( 
        //  at center, horizontal,vectical lookup
           check(turn, i-1,j) && check(turn, i+1, j) 
        || check(turn, i,j-1) && check(turn, i, j+1) 
        //  at center diagonal lookup
        || check(turn, i-1,j-1) && check(turn, i+1, j+1) 
        || check(turn, i-1,j+1) && check(turn, i+1, j-1) 
        // corner, horizontal lookup
        || check(turn, i+1,j) && check(turn, i+2, j) 
        || check(turn, i-1,j) && check(turn, i-2, j) 
        // corner, vertical lookup
        || check(turn, i,j-1) && check(turn, i, j-2) 
        || check(turn, i,j+1) && check(turn, i, j+2)
        // corner, primary diagnal
        || check(turn, i+1,j+1) && check(turn, i+2, j+2)
        || check(turn, i-1,j-1) && check(turn, i-2, j-2) 
        // corner, other diagonal
        || check(turn, i+1,j-1) && check(turn, i+2, j-2) 
        || check(turn, i-1,j+1) && check(turn, i-2, j+2) 
        ) {
            WINNER = turn;
            GAME_OVER = true;
        }
}

void initBoard() {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            board[i][j].pos = {START_X + SIZE*i + PADDING*i , 
                                          START_Y + SIZE*j + PADDING*j, SIZE, SIZE};        
            board[i][j].done = false;
            board[i][j].turn = FREE;
        }
    }
}
int main(void)
{    
    const int screenWidth = START_X*2 + (SIZE+PADDING)*GRID_SIZE;
    const int screenHeight = START_Y*2 + (SIZE+PADDING)*GRID_SIZE;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - keyboard input");

    SetTargetFPS(60);
    
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            board[i][j].pos = {START_X + SIZE*i + PADDING*i , 
                                          START_Y + SIZE*j + PADDING*j, SIZE, SIZE};        
            board[i][j].done = false;
            board[i][j].turn = FREE;
        }
    }
    turn = LEFT;
    int remaining = GRID_SIZE*GRID_SIZE;

    Texture2D xt = LoadTexture("x.png");   
    Texture2D ot = LoadTexture("o.png");   

    while (!WindowShouldClose())
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        BeginDrawing();

            ClearBackground(BLACK);
            
            if (GAME_OVER) {
                DrawText(WINNER == LEFT ? "LEFT WON" : "RIGHT WON", screenWidth/2 - 50, screenHeight/2, 20, WHITE);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                    GAME_OVER = false;
                    turn = LEFT;
                    initBoard();
                    remaining = GRID_SIZE*GRID_SIZE;
                }
            } else if (remaining == 0) {
                DrawText("It's a DRAW", screenWidth/2 - 50, screenHeight/2, 20, WHITE);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                    GAME_OVER = false;
                    turn = LEFT;
                    initBoard();
                    remaining = GRID_SIZE*GRID_SIZE;
                }
            } else {
                DrawText(turn == LEFT ? "Turn: LEFT" : "Turn: RIGHT", 10, 10, 20, WHITE);
            
                for (int i = 0; i < GRID_SIZE; ++i) {
                    for (int j = 0; j < GRID_SIZE; ++j) {
                        auto& b = board[i][j];
                        if (CheckCollisionPointRec(GetMousePosition(), b.pos)) {
                            Color c = LIGHTGRAY;
                            if (!b.done) {
                                if (turn == LEFT && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                                    --remaining;
                                    turn = RIGHT;
                                    b.done = true;
                                    b.turn = LEFT;
                                    
                                    DrawTexture(xt, START_X + SIZE*i + PADDING*i, START_Y + SIZE*j + PADDING*j, WHITE);
                                    checkWinner(LEFT, i, j);
                                } else if (turn == RIGHT && IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                                    --remaining;
                                    turn = LEFT;
                                    b.done = true;
                                    b.turn = RIGHT;
                                    
                                    DrawTexture(ot, START_X + SIZE*i + PADDING*i, START_Y + SIZE*j + PADDING*j, WHITE);
                                    checkWinner(RIGHT, i, j);
                                } else {
                                    // DrawRectangleRounded(b.pos, ROUNDEDNESS, 1, GREEN);
                                    DrawTexture(turn == LEFT ? xt : ot, START_X + SIZE*i + PADDING*i, START_Y + SIZE*j + PADDING*j, WHITE);
                                }
                            } else {
                                
                                    DrawTexture(b.turn == LEFT ? xt : ot, START_X + SIZE*i + PADDING*i, START_Y + SIZE*j + PADDING*j, WHITE);
                                
                            }

                                
                        } else {
                            if (b.done) {
                                DrawTexture(b.turn == LEFT ? xt : ot, START_X + SIZE*i + PADDING*i, START_Y + SIZE*j + PADDING*j, WHITE);
                            } else {
                                DrawRectangleRounded(b.pos, ROUNDEDNESS, 1, TurnColors[b.turn]);
                            }
                            
                        } 
                    }
                }
            }
        EndDrawing();

    }
    UnloadTexture(xt); 
    UnloadTexture(ot);
    CloseWindow();
    return 0;
}