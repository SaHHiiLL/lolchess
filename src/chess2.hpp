#ifndef CHESS2_
#define CHESS2_

#include <cstdint>
#include <string>
#include <unordered_map>
#include "../lib/raylib/src/raylib.h"


// 14 -> Black k
// 13 -> Bq
// 12 -> Br
// 11 -> Bb
// 10 -> Bn
// 9 -> Bp
//
// 6 -> White k
// 5 -> Wq
// 4 -> Wr
// 3 -> Wb
// 2 -> Wn
// 1 -> Wp
enum PieceColor {
    White = 0,
    Black = 8,
};
enum PieceType {
    Pawn = 1,
    Knight = 2,
    Bishop = 3,
    Rook = 4,
    Queen = 5,
    King = 6,
};

// Only convert to this if need DO not store this
class Piece {
public:
       Piece(uint16_t bits); 
};

class Board {
public:
    uint64_t bitboard;
    uint16_t pieces[64];
    std::unordered_map<uint16_t, Texture2D> texture_map;

    int board_size, square_size, x, y; // x and y represent where to start drawing the board

    void draw_board();
    void draw_pieces();
    void load_texture();
    void parse_hen(std::string fen);
    // Loads texture for an indivisual piece also crops the image so it can fit 
    // in each box
    Texture2D get_texture(uint16_t piece);

    Board(int size, int x, int y, std::string fen) {
        this->board_size = size;
        this->square_size = size / 8;
        this->x = x;
        this->y = y;
        this->load_texture();
        this->parse_hen(fen);
    }
};

#endif // CHESS2_
