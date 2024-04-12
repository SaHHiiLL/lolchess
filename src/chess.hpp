#ifndef CHESS
#define CHESS

#include <unordered_map>
#include <tuple>
#include <bits/stdc++.h> 
#include <raylib.h>

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
    White = 0,
    Black = 1,
};

enum PieceType {
    Pawn = 100,
    Knight = 300,
    Bishop = 310,
    Rook = 500,
    Queen = 800,
    King = -1,
};

class Piece {
    PieceColor color;
    PieceType type;
    int x;
    int y;

public:
    Piece(int color, int type, int x, int y);
    Texture2D get_texture();

    void setX(int x) {
        this->x = x;
    }
    void setY(int y) {
        this->x = y;
    }

    int getX() {
        return this->x;
    }
    int getY() {
        return this->y;
    }
};

class Board {
    std::unordered_map<std::tuple<PieceColor, PieceType>, Texture2D> texture_map;
    std::vector<Piece> pieces;
    void parse_fen(std::string);
    void load_textures();

public:
    Board(std::vector<Piece> p) {
        this->pieces = p;
    }
    Board();

    void draw(int size, int x_offset, int y_offset, std::unordered_map<std::tuple<int, int>, Texture2D, hash_tuple> texture_map);

    // @fen https://www.chess.com/terms/fen-chess
    void draw(int size, int x_offset, int y_offset, std::string fen);
    void draw(int size, std::string fen) {
        this->draw(size, 0, 0, fen);
    }
};
#endif // CHESS
