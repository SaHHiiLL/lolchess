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
                break;
            }
            case 'r': {
                // NOTE: same can be used to move the piece in the future?
                int idx = this->get_square(x++, y);
                uint16_t val = this->enum_to_num(PieceColor::Black, PieceType::Rook);
                this->pieces[idx] = val;
                break;
            } 
            case 'n': {
                int idx = this->get_square(x++, y);
                uint16_t val = this->enum_to_num(PieceColor::Black, PieceType::Knight);
                this->pieces[idx] = val;
                break;
            }
            case 'b': {
                int idx = this->get_square(x++, y);
                uint16_t val = this->enum_to_num(PieceColor::Black, PieceType::Bishop);
                this->pieces[idx] = val;
                break;
            }
            case 'q': {
                int idx = this->get_square(x++, y);
                uint16_t val = this->enum_to_num(PieceColor::Black, PieceType::Queen);
                this->pieces[idx] = val;
                break;
            }
            case 'k': {
                int idx = this->get_square(x++, y);
                uint16_t val = this->enum_to_num(PieceColor::Black, PieceType::King);
                this->pieces[idx] = val;
                break;
            }
            case 'p': {
                int idx = this->get_square(x++, y);
                uint16_t val = this->enum_to_num(PieceColor::Black, PieceType::Pawn);
                this->pieces[idx] = val;
                break;
            }
            case 'R': {
                int idx = this->get_square(x++, y);
                uint16_t val = this->enum_to_num(PieceColor::White, PieceType::Rook);
                this->pieces[idx] = val;
                break;
            }
            case 'B': {
                int idx = this->get_square(x++, y);
                uint16_t val = this->enum_to_num(PieceColor::White, PieceType::Bishop);
                this->pieces[idx] = val;
                break;
            }
            case 'N': {
                int idx = this->get_square(x++, y);
                uint16_t val = this->enum_to_num(PieceColor::White, PieceType::Knight);
                this->pieces[idx] = val;
                break;
            }
            case 'Q': {
                int idx = this->get_square(x++, y);
                uint16_t val = this->enum_to_num(PieceColor::White, PieceType::Queen);
                this->pieces[idx] = val;
                break;
            }
            case 'K': {
                int idx = this->get_square(x++, y);
                uint16_t val = this->enum_to_num(PieceColor::White, PieceType::King);
                this->pieces[idx] = val;
                break;
            }
            case 'P': {
                int idx = this->get_square(x++, y);
                uint16_t val = this->enum_to_num(PieceColor::White, PieceType::Pawn);
                this->pieces[idx] = val;
                break;
            }
            default: {
                char d = fen.at(i);
                if (std::isdigit(d)) {
                    x += d - '0';
                } else {
                    std::cerr << "Lol Invalid char at : " << i << "Char in question: " << d << std::endl;
                    exit(1);
                }
            }
        }
    }
    this->update_bitboard();
    std::cout << "Parse_fen " << this->bitboard << std::endl;
}

void Board::select_piece() {
    int idx = this->get_square(this->cursor.x, this->cursor.y);
    uint16_t piece = this->pieces[idx];
    if (piece == 0) {
        return;
    }
    if (!this->is_correct_piece_selected(piece)) {
        return;
    }

    if (this->cursor.x == this->selected.x && this->cursor.y == this->selected.y) {
        this->unselect_piece();
        return;
    }

    this->selected = {this->cursor.x, this->cursor.y};
    this->selected_piece = piece;
    this->has_selected_piece = true;
}

void Board::unselect_piece() {
    this->has_selected_piece = false;
    this->selected = {0, 0};
    this->selected_piece = 0;
}


// Comparing colors
bool Board::is_friendly(uint16_t c, uint16_t o) {
    bool p = this->num_to_enum(c).first == this->num_to_enum(o).first;
    // std::cout << std::boolalpha << p << std::endl;
    return p;
}

bool Board::is_correct_piece_selected(uint16_t piece) {
    bool p = this->turn == (piece < 8);
    // std::cout << std::boolalpha << p << std::endl;
    return p;
}

#define defer_this() do { goto defer; } while(0)

void Board::move_piece() {
    int next_square_idx = this->get_square(this->cursor.x, this->cursor.y);

    if (!this->has_selected_piece) {
        return;
    }

    // // Check if the selected piece is same as the one making the move
    
    // Constrains
    // 1. Piece can only move a free square or a square occupied by other piece
    // 2. A Piece can only move if it's their turn

    if (this->pieces[next_square_idx] != 0 ) { // checks if the square is occupied or not
        // sqaure is occupied
        if (this->is_friendly(this->pieces[next_square_idx], this->selected_piece)) {
            return;
        }
    }
    this->pieces[next_square_idx] = this->selected_piece;
    this->pieces[this->get_square(this->selected.x, this->selected.y)] = 0;
    this->update_bitboard();
    
defer:
    this->toggle_move();
}

void Board::move_cursor(int x, int y) {    
    if (this->cursor.x + x < 0 || this->cursor.x + x >= 8) {
        return;
    }
    if (this->cursor.y + y < 0 || this->cursor.y + y >= 8) {
        return;
    }
    this->cursor.x += x;
    this->cursor.y += y;
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

void Board::draw_board() {
    bool w_b = true;
    Color white = GetColor(0xEBECD0FF);
    Color black = GetColor(0x739552ff);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // Draws a blue square to indicate that the square is selected
            if (this->has_selected_piece == true && this->selected.x == j && this->selected.y == i) {
                DrawRectangle(
                    (j * this->square_size) + this->x, 
                    (i * this->square_size) + this->y, 
                    this->square_size, 
                    this->square_size,
                    BLUE
                );
            } else {
                if (this->cursor.x == j && this->cursor.y == i) {
                    DrawRectangle(
                        (j * this->square_size) + this->x, 
                        (i * this->square_size) + this->y, 
                        this->square_size, 
                        this->square_size,
                        RED
                    );
                } else {
                    DrawRectangle(
                        (j * this->square_size) + this->x, 
                        (i * this->square_size) + this->y, 
                        this->square_size, 
                        this->square_size,
                        (w_b == true ? white : black)
                    );
                }
            }
            auto key = std::tuple(i, j);
            this->draw_piece(j, i);
            w_b = !w_b;
        }
        w_b = !w_b;
    }
    this->debug_draw();
}

void Board::debug_draw() {
    if (!this->debug) {
        return;
    }
    DrawText("Debug", 10, 10, 20, RED);
    // Draw bitboard as debug
    std::string bitboard_str("Bitboard: ");
    bitboard_str.append(std::to_string(this->bitboard));

    DrawText(bitboard_str.c_str(), 10, 30, 20, RED);

    // Draw pieces as debug
    DrawFPS(10, 50);

    // Draw Mouse position
    Vector2 mouse = GetMousePosition();
    std::string mouse_str("Mouse: ");
    mouse_str.append(std::to_string(mouse.x));
    mouse_str.append(", ");
    mouse_str.append(std::to_string(mouse.y));
    DrawText(mouse_str.c_str(), 10, 70, 20, RED);
}

void Board::draw_piece(int x, int y) {
    int idx = this->get_square(x, y);
    uint16_t piece = this->pieces[idx];
    Texture2D texture = this->texture_map[piece];
    DrawTexture(texture, x * this->square_size + this->x, y * this->square_size + this->y, WHITE);
}
