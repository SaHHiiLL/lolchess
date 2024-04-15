#include "./chess3.hpp"
#include "../lib/raylib/src/raylib.h"

int main() {

    InitWindow(800, 850, "LolChess");
    SetTargetFPS(60);

    int board_size = 500;
    Game b(board_size, 100, 100, "r6r/1b2k1bq/8/8/7B/8/8/R3K2R");

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        b.draw_board();

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
