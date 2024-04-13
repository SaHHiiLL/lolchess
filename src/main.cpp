#include "./chess2.hpp"
#include "../lib/raylib/src/raylib.h"

int main() {

    InitWindow(500, 500, "LolChess");
    SetTargetFPS(60);

    int board_size = 480;
    Board b(board_size, 0, 0, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");

    while (!WindowShouldClose()) {
        BeginDrawing();
        b.draw_board();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
