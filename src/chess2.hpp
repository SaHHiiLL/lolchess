#ifndef CHESS2_
#define CHESS2_

#include <cstdint>
#include <iostream>
#include <ostream>
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
    uint64_t enum_to_num(PieceColor color, PieceType type) {
        return color | type;
    }
    std::pair<PieceColor, PieceType> num_to_enum(uint16_t pp) {
        int p = pp - 8;
        PieceColor color {};
        PieceType type = (PieceType) p;

        if (p < 0) {
            // White
            color = White;
        } else {
            // Black
            color = Black;
        }
        return std::make_pair(color, type);
    }

    int get_square(int x, int y) {
       // Calculate the position in the bitboard using x and y
        int square = y * 8 + x;
        return square;
    }

    void update_bitboard() {
        this->bitboard = 0;
        for (int i = 0; i < 64; i++) {
            if (this->pieces[i] != 0) {
                this->bitboard |= (1ULL << (63 - i));
            }
        }
    }
    bool debug = false;
    unsigned long long bitboard = 0;
    uint16_t pieces[64] = {0};
    std::unordered_map<uint16_t, Texture2D> texture_map = {};

    int board_size = 0,  square_size = 0, x = 0, y = 0; // x and y represent where to start drawing the board


    void print_piece(uint16_t piece[]);
    void debug_draw();
    void draw_piece(int x, int y);
    void load_texture();
    void parse_fen(std::string fen);
    // Loads texture for an indivisual piece also crops the image so it can fit 
    // in each box
    Texture2D get_texture(uint16_t piece);

    void print_bitboard() {
        for (int i = 0; i < 64; i++) {
            std::cout << ((bitboard >> (63 - i)) & 1);
        }
        std ::cout << std::endl << this->bitboard << std::endl;
        std::cout << std::endl;
    }


public:
    Vector2 cursor = {0, 0};
    Vector2 selected = {0, 0};
    bool has_selected_piece = false;
    uint16_t selected_piece = 0;

    // true represents WHITE to move and false represents BLACK
    bool turn = true;

    void toggle_move() {
        this->has_selected_piece = false;
        this->turn = !this->turn;
    }
    
    void move_piece();
    void move_cursor(int x, int y);
    void select_piece();
    bool is_friendly(uint16_t p, uint16_t o);
    bool is_correct_piece_selected(uint16_t p);
    void unselect_piece();


    void enable_debug() {
        this->debug = true;
    }
    void draw_board();

    // Constructor
    // Loads the texture for each piece and parses the fen
    // fen is the string that represents the board
    Board(int size, int x, int y, std::string fen) {
        this->board_size = size;
        this->square_size = size / 8;
        this->x = x;
        this->y = y;
        this->bitboard = 0;
        this->load_texture();
        this->parse_fen(fen);
    }
};

#endif // CHESS2_
