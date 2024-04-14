#include "./chess3.hpp"
#include <cstdint>
#include <iostream>
#include <ostream>
#include "../lib/raylib/src/raylib.h"

uint64_t Board::enum_to_num(PieceColor color, PieceType type) {
    return color | type;
}


std::pair<PieceColor, PieceType> Board::num_to_enum(uint16_t pp) {
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

int Board::get_square(int x, int y) {
    // Calculate the position in the bitboard using x and y
    // int square = y * 8 + x;
    int square = (7 - x) + (y * 8);
    return square;
}

Texture2D Game::get_texture(uint16_t piece) {

    int p = piece - 8;

    std::string image_file_name("target/alpha/con/");
    if (p < 0) {
        // White piece
        p+= 8;
        image_file_name.push_back('w');
    } else {
        image_file_name.push_back('b');
    }


    switch (p) {
        case 1: {
            image_file_name.push_back('P');
            break;
        }
        case 2: {
            image_file_name.push_back('N');
            break;
        }
        case 3: {
            image_file_name.push_back('B');
            break;
        }
        case 4: {
            image_file_name.push_back('R');
            break;

        }
        case 5: {
            image_file_name.push_back('Q');
            break;
        }
        case 6: {
            image_file_name.push_back('K');
            break;
        }
    }
    image_file_name.append(".svg.png");

    Image img = LoadImage(image_file_name.c_str());
    ImageResize(&img, this->square_size, this->square_size); 
    Texture2D t = LoadTextureFromImage(img);
    UnloadImage(img);
    return t;
}

void Game::load_texture() {
    uint16_t known_pieces[] = {
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
    int known_pieces_size = 12;

    for (int i = 0; i < known_pieces_size; i++) {
        std::cout << known_pieces[i] << std::endl;
        Texture2D texture = this->get_texture(known_pieces[i]);
        this->texture_map.insert(std::make_pair(known_pieces[i], texture));
    }
}

void Board::load_position_from_fen(std::string fen) {
    int x = 0, y = 0;
    for (size_t i = 0; i < fen.length(); i++) {
        switch (fen.at(i)) {
            case '/': {
                y++;
                x = 0;
                break;
            }
            case 'r': {
                int idx = this->get_square(x++, y);
                std::cout << "Rook at: " << idx << std::endl;
                this->black_rook_bitboard |= (1ULL << (63 - idx));
                break;
            } 
            // case 'n': {
            //     int idx = this->get_square(x++, y);
            //     this->black_knight_bitboard |= (1ULL << (63 - idx));
            //     break;
            // }
            // case 'b': {
            //     int idx = this->get_square(x++, y);
            //     this->black_bishop_bitboard |= (1ULL << (63 - idx));
            //     break;
            // }
            // case 'q': {
            //     int idx = this->get_square(x++, y);
            //     this->black_queen_bitboard |= (1ULL << (63 - idx));
            //     break;
            // }
            // case 'k': {
            //     int idx = this->get_square(x++, y);
            //     this->black_king_bitboard |= (1ULL << (63 - idx));
            //     break;
            // }
            // case 'p': {
            //     int idx = this->get_square(x++, y);
            //     this->black_pawn_bitboard |= (1ULL << (63 - idx));
            //     break;
            // }
            // case'R': {
            //     int idx = this->get_square(x++, y);
            //     this->white_rook_bitboard |= (1ULL << (63 - idx));
            //     break;
            // }
            // case 'B': {
            //     int idx = this->get_square(x++, y);
            //     this->white_bishop_bitboard |= (1ULL << (63 - idx));
            //     break;
            // }
            // case 'N': {
            //     int idx = this->get_square(x++, y);
            //     this->white_knight_bitboard |= (1ULL << (63 - idx));
            //     break;
            // }
            // case 'Q': {
            //     int idx = this->get_square(x++, y);
            //     this->white_queen_bitboard |= (1ULL << (63 - idx));
            //     break;
            // }
            // case 'K': {
            //     int idx = this->get_square(x++, y);
            //     this->white_king_bitboard |= (1ULL << (63 - idx));
            //     break;
            // }
            // case 'P': {
            //     int idx = this->get_square(x++, y);
            //     this->white_pawn_bitboard |= (1ULL << (63 - idx));
            //     break;
            // }
            default: {
                char d = fen.at(i);
                if (std::isdigit(d)) {
                    x += d - '0';
                } else {
                    x++;
                    // std::cerr << "Lol Invalid char at : " << i << "Char in question: " << d << std::endl;
                    // exit(1);
                }
            }
        }
    }
}

void Game::draw_board() {
    bool w_b = true;
    Color white = GetColor(0xEBECD0FF);
    Color black = GetColor(0x739552ff);

    //         // 63 62 61 60 59 58 57 56
    //         // 55 54 53 52 51 50 49 48
    //         // 47 46 45 44 43 42 41 40
    //         // 39 38 37 36 35 34 33 32
    //         // 31 30 29 28 27 26 25 24
    //         // 23 22 21 20 19 18 17 16
    //         // 15 14 13 12 11 10 09 08
    //         // 07 06 05 04 03 02 01 00


    for (int i = 0; i < 64; i++) {
        int x = i % 8;
        int y = i / 8;
        DrawRectangle(
            (x * this->square_size) + this->x, 
            (y * this->square_size) + this->y, 
            this->square_size, 
            this->square_size,
            (w_b == true ? white : black)
        );
        this->draw_piece(i);
        w_b = !w_b;
        if (x == 7) {
            w_b = !w_b;
        }
    }
}

bool is_k_bit_set(int n, int k)
{
    return (n & ( 1 << k )) >> k;
}

uint16_t Board::get_piece_at_square(int idx) {
    // Get the idx and then check every bitboard to see if the piece is there
    // idfk if this is a good way to do it but it works :)

    if (is_k_bit_set(this->board_bitboard(), idx)) {
        PieceColor color;
        PieceType type;

        if (is_k_bit_set(this->white_bitboard(), idx)) {
            color = White;
        }
        if (is_k_bit_set(this->black_bitboard(), idx)) {
            color = Black;
        }

        if (is_k_bit_set(this->white_pawn_bitboard, idx)) {
            type = PieceType::Pawn;
        } else if (is_k_bit_set(this->white_knight_bitboard, idx)) {
            type = PieceType::Knight;
        } else if (is_k_bit_set(this->white_bishop_bitboard, idx)) {
            type = PieceType::Bishop;
        } else if (is_k_bit_set(this->white_rook_bitboard, idx)) {
            type = PieceType::Rook;
        } else if (is_k_bit_set(this->white_queen_bitboard, idx)) {
            type = PieceType::Queen;
        } else if (is_k_bit_set(this->white_king_bitboard, idx)) {
            type = PieceType::King;
        } else if (is_k_bit_set(this->black_pawn_bitboard, idx)) {
            type = PieceType::Pawn;
        } else if (is_k_bit_set(this->black_knight_bitboard, idx)) {
            type = PieceType::Knight;
        } else if (is_k_bit_set(this->black_bishop_bitboard, idx)) {
            type = PieceType::Bishop;
        } else if (is_k_bit_set(this->black_rook_bitboard, idx)) {
            type = PieceType::Rook;
        } else if (is_k_bit_set(this->black_queen_bitboard, idx)) {
            type = PieceType::Queen;
        } else if (is_k_bit_set(this->black_king_bitboard, idx)) {
            type = PieceType::King;
        } else {
            std::cerr << "Lol Invalid piece at idx: " << idx << std::endl;
            exit(1);
        }
        auto res = this->enum_to_num(color, type);
        return res;
    }
    return 0;
}

void Game::draw_piece(int idx) {
    ///TODO: fix this function
}

