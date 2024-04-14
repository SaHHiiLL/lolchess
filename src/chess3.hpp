#ifndef CHESS3_HPP
#define CHESS3_HPP
#include <cstdint>
#include <iostream>
#include <ostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
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
class Board {

public:

    uint64_t white_pawn_bitboard = { 0 };
    uint64_t white_rook_bitboard = { 0 };
    uint64_t white_king_bitboard = { 0 };
    uint64_t white_queen_bitboard = { 0 };
    uint64_t white_bishop_bitboard = { 0 };
    uint64_t white_knight_bitboard = { 0 };

    uint64_t black_pawn_bitboard = { 0 };
    uint64_t black_rook_bitboard = { 0 };
    uint64_t black_king_bitboard = { 0 };
    uint64_t black_queen_bitboard = { 0 };
    uint64_t black_bishop_bitboard = { 0 };
    uint64_t black_knight_bitboard = { 0 };

    uint64_t white_bitboard() {
        return white_knight_bitboard | white_bishop_bitboard | white_pawn_bitboard | white_rook_bitboard | white_king_bitboard | white_queen_bitboard;
    }

    uint64_t black_bitboard() {
        return black_knight_bitboard | black_bishop_bitboard | black_pawn_bitboard | black_rook_bitboard | black_king_bitboard | black_queen_bitboard; 
    }

    uint64_t board_bitboard() {
        return white_bitboard() | black_bitboard(); 
    }

    uint64_t bishop_bitboard() {
        return white_bishop_bitboard | black_bishop_bitboard;
    }

    uint64_t knight_bitboard() {
        return white_knight_bitboard | black_knight_bitboard;
    }

    uint64_t pawn_bitboard() {
        return white_pawn_bitboard | black_pawn_bitboard;
    }

    uint64_t rook_bitboard() {
        return white_rook_bitboard | black_rook_bitboard;
    }

    uint64_t king_bitboard() {
        return white_king_bitboard | black_king_bitboard;
    }

    uint64_t queen_bitboard() {
        return white_queen_bitboard | black_queen_bitboard;
    }

    std::vector<uint64_t> known_pieces = {
        PieceColor::Black | PieceType::King,
        PieceColor::Black | PieceType::Queen,
        PieceColor::Black | PieceType::Rook,
        PieceColor::Black | PieceType::Bishop,
        PieceColor::Black | PieceType::Knight,
        PieceColor::Black | PieceType::Pawn,

        PieceColor::White | PieceType::King,
        PieceColor::White | PieceType::Queen,
        PieceColor::White | PieceType::Rook,
        PieceColor::White | PieceType::Bishop,
        PieceColor::White | PieceType::Knight,
        PieceColor::White | PieceType::Pawn,
    };

    // Coverts enums to a piece number
    uint64_t enum_to_num(PieceColor color, PieceType type);
    // Converts piece number to a colour and type enums
    std::pair<PieceColor, PieceType> num_to_enum(uint16_t pp);
    // Get the idx of a square of represented in 1D array
    int get_square(int x, int y);
    // Parses fen
    void load_position_from_fen(std::string fen);
    // Get piece at a square
    uint16_t get_piece_at_square(int y);

    void debug_print() {
        std::cout << "White pawn: " << white_pawn_bitboard << std::endl;
        std::cout << "White rook: " << white_rook_bitboard << std::endl;
        std::cout << "White king: " << white_king_bitboard << std::endl;
        std::cout << "White queen: " << white_queen_bitboard << std::endl;
        std::cout << "White bishop: " << white_bishop_bitboard << std::endl;
        std::cout << "White knight: " << white_knight_bitboard << std::endl;

        std::cout << "Black pawn: " << black_pawn_bitboard << std::endl;
        std::cout << "Black rook: " << black_rook_bitboard << std::endl;
        std::cout << "Black king: " << black_king_bitboard << std::endl;
        std::cout << "Black queen: " << black_queen_bitboard << std::endl;
        std::cout << "Black bishop: " << black_bishop_bitboard << std::endl;
        std::cout << "Black knight: " << black_knight_bitboard << std::endl;

        std::cout << "White bitboard: " << white_bitboard() << std::endl;
        std::cout << "Black bitboard: " << black_bitboard() << std::endl;

        std::cout << "Board bitboard: " << board_bitboard() << std::endl;
    }
};

class Game {
    int size = 480;
    int x = 0;
    int y = 0;
    int square_size;

    Board b{ };

    std::unordered_map<uint16_t, Texture2D> texture_map = {};

public:
    Game (int size, int x, int y, std::string fen) {
        this->size = size;
        this->x = x;
        this->y = y;
        this->square_size = this->size / 8;
        this->load_texture();
        this->b.load_position_from_fen(fen);
        this->b.debug_print();
    }
    // Draws the board
    void draw_board();
    // Draw the pieces
    void draw_piece(int i);
    // Loads texture for all the pieces
    void load_texture();
    // Get texture of a single piece
    Texture2D get_texture(uint16_t piece);

};


#endif // CHESS3_HPP
