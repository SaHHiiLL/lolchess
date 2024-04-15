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
        if (IsKeyPressed(KEY_W)) {
            b.move_cursor(0, -1);
        } else if (IsKeyPressed(KEY_S)) {
            b.move_cursor(0, 1);
        } else if (IsKeyPressed(KEY_A)) {
            b.move_cursor(-1, 0);
        } else if (IsKeyPressed(KEY_D)) {
            b.move_cursor(1, 0);
        } else if (IsKeyPressed(KEY_ENTER)) {
            if (b.is_selected()) {
                b.move_piece();
            } else {
                b.select_piece();
            }
        } else if (IsKeyPressed(KEY_BACKSPACE)) {
            b.print_debug();
        }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
