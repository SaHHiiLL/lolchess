#include "./chess.hpp"
#include <raylib.h>

int main() {

    InitWindow(1000, 1000, "LolChess");
    SetTargetFPS(60);

    int board_size = 627;

    // for (auto& it : image_map) {
    //     std::cout << "Loading image" << std::endl;
    //     Image img = LoadImage(it.second.c_str());
    //
    //     ImageResize(&img, board_size / 8, board_size / 8);
    //     Texture2D texture = LoadTextureFromImage(img);
    //     UnloadImage(img);
    //     std::cout << "Image Loaded" << std::endl;
    //     texture_map.insert_or_assign(it.first, texture);
    // }

    while (!WindowShouldClose()) {
        BeginDrawing();
        Board b;
        b.draw(board_size, 60, 60, texture_map);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
