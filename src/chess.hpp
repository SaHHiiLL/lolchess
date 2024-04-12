#ifndef CHESS
#define CHESS

#include <unordered_map>
#include <tuple>
#include <bits/stdc++.h> 
#include "../lib/raylib/src/raylib.h"

// A hash function used to hash a tuple 
struct hash_tuple { 

    template <class T1, class T2> 

    size_t operator()( 
        const std::tuple<T1, T2>& x) 
    const
    { 
        return std::get<0>(x) 
        ^ std::get<1>(x);
    } 
};

enum PieceColor {
    White = 8,
    Black = 16,
};

enum PieceType {
    Pawn = 1,
    Knight = 2,
    Bishop = 3,
    Rook = 4,
    Queen = 5,
    King = 6,
};

class Piece {
    PieceColor color;
    PieceType type;
    int x;
    int y;

public:

    // Drawing position
    void draw(int x, int y);
    Piece(PieceColor color, PieceType type, int x, int y) {
        this->type = type;
        this->color = color;
        this->x = x;
        this->y = y;
    }


    void setX(int x) {
        this->x = x;
    }
    void setY(int y) {
        this->x = y;
    }

    PieceColor get_color() {
        return this->color;
    }

    PieceType get_type() {
        return this->type;
    }

    int getX() {
        return this->x;
    }
    int getY() {
        return this->y;
    }
};

class Board {
    std::unordered_map<std::tuple<PieceColor, PieceType>, Texture2D, hash_tuple> texture_map;
    std::vector<Piece> pieces;
    int size, x_offset, y_offset, square_size;

    void parse_fen(std::string);
    void load_textures();
    Texture2D get_texture(int color, int type);

    // Represents the board - but only indicated if the a square is occupied or not -- will be used to index the `pieces_arr`
    unsigned long long bitbord;
    // Represents all pieces in an array as 16bit integers, where the first 2 bits represents the colour and rest of them represents type
    uint16_t pieces_arr[64];

public:
    void Debug() {
        std::cout << "DEBUGGING THIS " << std::endl;
        std::cout << this->pieces.size() << std::endl;
        std::cout << this->texture_map.size() << std::endl;
        std::cout << this->size << std::endl;
        std::cout << this->x_offset << std::endl;
        std::cout << this->y_offset << std::endl;
        std::cout << this->square_size << std::endl;
    }
    Board(std::string fen, int size, int x_off, int y_off) {
        this->size = size;
        this->x_offset = x_off;
        this->y_offset = y_off;
        this->square_size = this->size / 8;
        this->parse_fen(fen);
        this->load_textures();
    }

    // @fen https://www.chess.com/terms/fen-chess
    void draw();

    void drawPieces();

};
#endif // CHESS
