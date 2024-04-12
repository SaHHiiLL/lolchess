#include "./chess.hpp"
#include "../raylib/src/raylib.h"

int main() {

    InitWindow(500, 500, "LolChess");
    SetTargetFPS(60);

    int board_size = 480;

    Board b("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR", board_size, 0, 0);
    b.Debug();

    while (!WindowShouldClose()) {
        BeginDrawing();
        b.draw();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
