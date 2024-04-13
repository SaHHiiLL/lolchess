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

    // void load_bitboard() {
    //     for (int i = 0; i < 64; i++) {
    //         if (this->pieces[i] != 0) {
    //             this->update_bitboard(i);
    //         }
    //     }
    // }
    //
    // void update_bitboard(int pos) {
    //     this->bitboard |= (1ULL << (63 - pos));
    // }


public:
    bool debug = false;
    unsigned long long bitboard;
    uint16_t pieces[64];
    std::unordered_map<uint16_t, Texture2D> texture_map;

    int board_size, square_size, x, y; // x and y represent where to start drawing the board

    void enable_debug() {
        this->debug = true;
    }

    void print_piece(uint16_t piece[]);
    void debug_draw();
    void draw_board();
    void draw_piece(int x, int y);
    void load_texture();
    void parse_fen(std::string fen);
    // Loads texture for an indivisual piece also crops the image so it can fit 
    // in each box
    Texture2D get_texture(uint16_t piece);


    void print_bitboard() {
        for (int i = 0; i < 64; i++) {
            // if (i % 8 == 0) {
            //     std::cout << std::endl;
            // }
            std::cout << ((bitboard >> (63 - i)) & 1);
        }
        std ::cout << std::endl << this->bitboard << std::endl;
        std::cout << std::endl;
    }


    Board(int size, int x, int y, std::string fen) {
        this->board_size = size;
        this->square_size = size / 8;
        this->x = x;
        this->y = y;
        this->bitboard = 0;
        for (int i = 0; i < 64; i++) {
            this->pieces[i] = 0;
        }
        this->load_texture();
        this->parse_fen(fen);
    }
};

#endif // CHESS2_
