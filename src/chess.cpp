#include "./chess.hpp"
#include "../lib/raylib/src/raylib.h"
#include <unordered_map>
#include <tuple>

void Board::draw() {
    bool w_b = true;

    Color white = GetColor(0xEBECD0FF);
    Color black = GetColor(0x739552ff);
    for (int i = 0; i < 8; i++) {

        for (int j = 0; j < 8; j++) {

            DrawRectangle(
                (j * this->square_size) + this->x_offset, 
                (i * this->square_size) + this->y_offset, 
                this->square_size, 
                this->square_size,
                (w_b == true ? white : black)
            );
            auto key = std::tuple(i, j);
            this->drawPieces();
            w_b = !w_b;
        }
        w_b = !w_b;
    }
}

void Board::drawPieces() {
    for (size_t i = 0; i < this->pieces.size(); i++) {
        auto p = this->pieces.at(i);
        auto key = std::make_tuple(p.get_color(), p.get_type()); 

        if (texture_map.find(key) != texture_map.end()) {
            Texture2D texture = this->texture_map.at(key);
            DrawTexture(texture_map.at(key),  (p.getX() * this->square_size) + this->x_offset, (p.getY() * this->square_size) + this->y_offset, WHITE);
        }
    }
}

void Board::load_textures() {
    std::vector<std::tuple<PieceColor, PieceType>> pairs = {
        std::make_tuple(PieceColor::Black, PieceType::Pawn),
        std::make_tuple(PieceColor::Black, PieceType::Queen),
        std::make_tuple(PieceColor::Black, PieceType::King),
        std::make_tuple(PieceColor::Black, PieceType::Rook),
        std::make_tuple(PieceColor::Black, PieceType::Knight),
        std::make_tuple(PieceColor::Black, PieceType::Bishop),

        std::make_tuple(PieceColor::White, PieceType::Pawn),
        std::make_tuple(PieceColor::White, PieceType::Queen),
        std::make_tuple(PieceColor::White, PieceType::King),
        std::make_tuple(PieceColor::White, PieceType::Rook),
        std::make_tuple(PieceColor::White, PieceType::Knight),
        std::make_tuple(PieceColor::White, PieceType::Bishop),
    };

    for (std::tuple<PieceColor, PieceType> p: pairs) {
        Texture2D texture = this->get_texture(std::get<0>(p), std::get<1>(p));
        this->texture_map.insert(std::make_pair(p, texture));
    }
}

Texture2D Board::get_texture(int color, int type) {
    std::string image_file_name("target/alpha/con/");
    if (color == PieceColor::Black) {
        image_file_name.push_back('b');
    } else {
        image_file_name.push_back('w');
    }

    switch (type) {
        case PieceType::King: {
            image_file_name.push_back('K');
            break;
        } 
        case PieceType::Knight: {
            image_file_name.push_back('N');
            break;
        }
        case PieceType::Queen: {
            image_file_name.push_back('Q');
            break;
        }
        case PieceType::Pawn: {
            image_file_name.push_back('P');
            break;
        }
        case PieceType::Bishop: {
            image_file_name.push_back('B');
            break;
        }
        case PieceType::Rook: {
            image_file_name.push_back('R');
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

void Board::parse_fen(std::string fen) {
    std::vector<Piece> p;
    int x = 0;
    int y = 0;

    for (size_t i = 0; i < fen.length(); i++) {
        switch (fen.at(i)) {
            case '/': {
                y++;
                x = 0;
                continue;
            }
            case 'r': {
                // Black rook
                p.push_back(Piece(PieceColor::Black, PieceType::Rook, x++, y));
                break;
            }
            case 'n': {
                // Black knight
                p.push_back(Piece(PieceColor::Black, PieceType::Knight, x++, y));
                break;
            }

            case 'q': {
                // Black Queen 
                p.push_back(Piece(PieceColor::Black, PieceType::Queen, x++, y));
                break;
            }
            case 'b': {
                // Black Bishop 
                p.push_back(Piece(PieceColor::Black, PieceType::Bishop, x++, y));
                break;
            }
            case 'k': {
                // Black King 
                p.push_back(Piece(PieceColor::Black, PieceType::King, x++, y));
                break;
            }
            case 'p': {
                // Black Pawn 
                p.push_back(Piece(PieceColor::Black, PieceType::Pawn, x++, y));
                break;
            }
            case 'R': {
                // White rook
                p.push_back(Piece(PieceColor::White, PieceType::Rook, x++, y));
                break;
            }
            case 'N': {
                // White knight
                p.push_back(Piece(PieceColor::White, PieceType::Knight, x++, y));
                break;
            }
            case 'Q': {
                // White Queen 
                p.push_back(Piece(PieceColor::White, PieceType::Queen, x++, y));
                break;
            }
            case 'B': {
                // White Bishop 
                p.push_back(Piece(PieceColor::White, PieceType::Bishop, x++, y));
                break;
            }
            case 'K': {
                // White King 
                p.push_back(Piece(PieceColor::White, PieceType::King, x++, y));
                break;
            }
            case 'P': {
                // White Pawn 
                p.push_back(Piece(PieceColor::White, PieceType::Pawn, x++, y));
                break;
            }
            default: {
                char d = fen.at(i);
                if (std::isdigit(d)) {
                    x += int(d);
                } else {
                    std::cerr << "Lol Invalid char at : " << i << "Char in question: " << d << std::endl;
                }
            }
        }
    }

    this->pieces = p;
}


