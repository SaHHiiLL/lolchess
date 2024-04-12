#include "./chess.hpp"
#include <raylib.h>
#include <unordered_map>
#include <tuple>

// DEPERECATED
void Board::draw(int size, int x_offset, int y_offset, std::unordered_map<std::tuple<int, int>, Texture2D, hash_tuple> texture_map) {

    size = size / 8;
    bool w_b = true;

    Color white = GetColor(0xEBECD0FF);
    Color black = GetColor(0x739552ff);
    for (int i = 0; i < 8; i++) {

        for (int j = 0; j < 8; j++) {

            DrawRectangle((j * size) + x_offset, (i * size) + y_offset, size, size,(w_b == true ? white : black) );
            auto key = std::tuple(i, j);
            if (texture_map.find(key) != texture_map.end()) {
                DrawTexture(texture_map.at(key),  (j * size) + x_offset, (i * size) + y_offset, WHITE);
            }

            w_b = !w_b;
        }
        w_b = !w_b;
    }
}

void Board::load_textures() {
    // TODO: throw an error
    if (this->pieces.empty()) {
        return;
    }
    
    for (size_t i = 0; i < this->pieces.size(); i++) {
        this->pieces.at(i).get_texture();
    }

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
        }

        char d = fen.at(i);

        if (std::isdigit(d)) {
            x += int(d);
        } else {
            std::cerr << "Lol Invalid char at : " << i << "Char in question: " << d << std::endl;
        }
    }

    this->pieces = p;
}

void Board::draw(int size, int x_offset, int y_offset, std::string fen) {
    this->parse_fen(fen);
}
