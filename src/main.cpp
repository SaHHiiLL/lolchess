#include "./chess2.hpp"
#include "../lib/raylib/src/raylib.h"

int main() {

    InitWindow(800, 850, "LolChess");
    SetTargetFPS(60);

    int board_size = 500;
    Board b(board_size, 100, 100, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
    b.enable_debug();

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        b.draw_board();

        if (IsKeyPressed(KEY_W)) {
            b.move_cursor(0, -1);
        } else if (IsKeyPressed(KEY_S)) {
            b.move_cursor(0, 1);
        } else if (IsKeyPressed(KEY_A)) {
            b.move_cursor(-1, 0);
        } else if (IsKeyPressed(KEY_D)) {
            b.move_cursor(1, 0);
        } else if (IsKeyPressed(KEY_ENTER)) {
            if (b.has_selected_piece) {
                b.move_piece();
            } else {
                b.select_piece();
            }
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
