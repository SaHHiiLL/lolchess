#include "./chess.hpp"
#include "../lib/raylib/src/raylib.h"

int main() {

    InitWindow(800, 850, "LolChess");
    SetTargetFPS(60);

    int board_size = 500;
    Game b(board_size, 100, 100);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        b.draw_board();
        // TODO: remoev keyboard controls  
        if (IsKeyPressed(KEY_W)) {
            b.move_cursor(0, -1);
        } else if (IsKeyPressed(KEY_S)) {
            b.move_cursor(0, 1);
        } else if (IsKeyPressed(KEY_A)) {
            b.move_cursor(-1, 0);
        } else if (IsKeyPressed(KEY_D)) {
            b.move_cursor(1, 0);
        } else if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (b.is_selected()) {
                b.move_piece();
            } else {
                b.select_piece();
            }
        } else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
            b.unselect_piece();
        } else if (IsKeyPressed(KEY_BACKSPACE)) {
            b.print_debug();
        }

        b.mouse_cursor();

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
