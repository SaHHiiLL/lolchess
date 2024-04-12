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

void Board::parse_hen(std::string fen) {
    int x, y;
    for (size_t i = 0; i < fen.length(); i++) {
        switch (fen.at(i)) {
            case '/': {
                y++;
                x=0;
                continue;
            }
            case 'r': {
                
            }
        }
    }
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

    // https://stackoverflow.com/a/26230537
    // Moves the Starts from left 
    int n_bytes_to_move = 1;
    int colour_bit = (piece >> n_bytes_to_move) & 1;
    std::string image_file_name("target/alpha/con/");

    if (colour_bit == 1) {
        image_file_name.push_back('b');
        // Black so we can minus it
        piece = piece - 8;
    } else {
        image_file_name.push_back('w');
    }

    switch (piece) {
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
