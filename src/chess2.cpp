#include "./chess2.hpp"
#include <iostream>

void Board::load_texture() {
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

void Board::parse_fen(std::string fen) {
    int x = 0, y = 0;
    for (size_t i = 0; i < fen.length(); i++) {
        switch (fen.at(i)) {
            case '/': {
                y++;
                x = 0;
                continue;
            }
            case 'r': {
                // NOTE: same can be used to move the piece in the future?
                int idx = this->set_bitboard(x++, y);
                uint16_t val = this->enum_to_num(PieceColor::Black, PieceType::Rook);
                this->pieces[idx] = val;
                break;
            } 
            case 'n': {
                int idx = this->set_bitboard(x++, y);
                uint16_t val = this->enum_to_num(PieceColor::Black, PieceType::Knight);
                this->pieces[idx] = val;
                break;
            }
            case 'b': {
                int idx = this->set_bitboard(x++, y);
                uint16_t val = this->enum_to_num(PieceColor::Black, PieceType::Bishop);
                this->pieces[idx] = val;
                break;
            }
            case 'q': {
                int idx = this->set_bitboard(x++, y);
                uint16_t val = this->enum_to_num(PieceColor::Black, PieceType::Queen);
                this->pieces[idx] = val;
                break;
            }
            case 'k': {
                int idx = this->set_bitboard(x++, y);
                uint16_t val = this->enum_to_num(PieceColor::Black, PieceType::King);
                this->pieces[idx] = val;
                break;
            }
            case 'p': {
                int idx = this->set_bitboard(x++, y);
                uint16_t val = this->enum_to_num(PieceColor::Black, PieceType::Pawn);
                this->pieces[idx] = val;
                break;
            }
            case 'R': {
                int idx = this->set_bitboard(x++, y);
                uint16_t val = this->enum_to_num(PieceColor::White, PieceType::Rook);
                this->pieces[idx] = val;
                break;
            }
            case 'B': {
                int idx = this->set_bitboard(x++, y);
                uint16_t val = this->enum_to_num(PieceColor::White, PieceType::Bishop);
                this->pieces[idx] = val;
                break;
            }
            case 'N': {
                int idx = this->set_bitboard(x++, y);
                uint16_t val = this->enum_to_num(PieceColor::White, PieceType::Knight);
                this->pieces[idx] = val;
                break;
            }
            case 'Q': {
                int idx = this->set_bitboard(x++, y);
                uint16_t val = this->enum_to_num(PieceColor::White, PieceType::Queen);
                this->pieces[idx] = val;
                break;
            }
            case 'K': {
                int idx = this->set_bitboard(x++, y);
                uint16_t val = this->enum_to_num(PieceColor::White, PieceType::King);
                this->pieces[idx] = val;
                break;
            }
            case 'P': {
                int idx = this->set_bitboard(x++, y);
                uint16_t val = this->enum_to_num(PieceColor::White, PieceType::Pawn);
                this->pieces[idx] = val;
                break;
            }
        }
    }
    std::cout << "Parse_fen " << this->bitboard << std::endl;
}


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

// (n & ( 1 << k )) >> k
// where K represents the wanted bits and n is the number 
Texture2D Board::get_texture(uint16_t piece) {

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
// void Board::draw() {
//     bool w_b = true;
//
//     Color white = GetColor(0xEBECD0FF);
//     Color black = GetColor(0x739552ff);
//     for (int i = 0; i < 8; i++) {
//
//         for (int j = 0; j < 8; j++) {
//
//             DrawRectangle(
//                 (j * this->square_size) + this->x_offset, 
//                 (i * this->square_size) + this->y_offset, 
//                 this->square_size, 
//                 this->square_size,
//                 (w_b == true ? white : black)
//             );
//             auto key = std::tuple(i, j);
//             this->drawPieces();
//             w_b = !w_b;
//         }
//         w_b = !w_b;
//     }
// }

void Board::draw_board() {
    bool w_b = true;
    Color white = GetColor(0xEBECD0FF);
    Color black = GetColor(0x739552ff);
    for (int i = 0; i < 8; i++) {

        for (int j = 0; j < 8; j++) {

            DrawRectangle(
                (j * this->square_size) + this->x, 
                (i * this->square_size) + this->y, 
                this->square_size, 
                this->square_size,
                (w_b == true ? white : black)
            );
            auto key = std::tuple(i, j);
            this->draw_pieces();
            w_b = !w_b;
        }
        w_b = !w_b;
    }
}

//
// void Board::drawPieces() {
//     for (size_t i = 0; i < this->pieces.size(); i++) {
//         auto p = this->pieces.at(i);
//         auto key = std::make_tuple(p.get_color(), p.get_type()); 
//
//         if (texture_map.find(key) != texture_map.end()) {
//             Texture2D texture = this->texture_map.at(key);
//             DrawTexture(texture_map.at(key),  (p.getX() * this->square_size) + this->x_offset, (p.getY() * this->square_size) + this->y_offset, WHITE);
//         }
//     }
// }


void Board::draw_pieces() {
    unsigned long long n = this->bitboard;

    int index = 0;

    for (size_t i = 0; n; i++, n >>=1) {
        if (n & 1) {
            int y = i / 8; // Convert index to y coordinate
            int x = i % 8; // Convert index to x coordinate

            // std::cout << this->pieces[i] << std::endl;
            // Gets the texture from the map
            // For now will just assume that there will always be a valid key
            // DrawTexture(this->texture_map.at(this->pieces[i]);
            //
            DrawTexture(texture_map.at(this->pieces[i]),
                        (x * this->square_size)+ this->x,
                        (y * this->square_size) + this->y,
                        WHITE);
        }
    }
}

