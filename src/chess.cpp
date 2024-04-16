#include "./chess.hpp"
#include <cassert>
#include <cstdint>
#include <iostream>
#include <ostream>
#include "../lib/raylib/src/raylib.h"

uint64_t Board::enum_to_num(PieceColor color, PieceType type) {
    return color | type;
}

void print_texture_map(std::unordered_map<uint16_t, Texture2D> texture_map) {
    for (auto const& [key, val] : texture_map) {
        std::cout << key << " " << val.id << std::endl;
    }
    exit(1);  
}


std::pair<PieceColor, PieceType> Board::num_to_enum(uint16_t pp) {
    int p = pp - 8;
    PieceColor color {};
    PieceType type = (PieceType) p;

    if (p < 0) {
        // White
        p += 8;
        color = White;
    } else {
        // Black
        color = Black;
    }
    return std::make_pair(color, type);
}

int Board::get_square(int x, int y) {
    // Calculate the index of the square in the 1D array
    int square = (x) + (y * 8);
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
                this->black_rook_bitboard |= (1ULL << (63 - idx));
                this->board[idx] = PieceColor::Black | PieceType::Rook;
                break;
            } 
            case 'n': {
                int idx = this->get_square(x++, y);
                this->black_knight_bitboard |= (1ULL << (63 - idx));
                this->board[idx] = PieceColor::Black | PieceType::Knight;
                break;
            }
            case 'b': {
                int idx = this->get_square(x++, y);
                this->black_bishop_bitboard |= (1ULL << (63 - idx));
                this->board[idx] = PieceColor::Black | PieceType::Bishop;
                break;
            }
            case 'q': {
                int idx = this->get_square(x++, y);
                this->black_queen_bitboard |= (1ULL << (63 - idx));
                this->board[idx] = PieceColor::Black | PieceType::Queen;
                break;
            }
            case 'k': {
                int idx = this->get_square(x++, y);
                this->black_king_bitboard |= (1ULL << (63 - idx));
                this->board[idx] = PieceColor::Black | PieceType::King;
                break;
            }
            case 'p': {
                int idx = this->get_square(x++, y);
                this->black_pawn_bitboard |= (1ULL << (63 - idx));
                this->board[idx] = PieceColor::Black | PieceType::Pawn;
                break;
            }
            case'R': {
                int idx = this->get_square(x++, y);
                this->white_rook_bitboard |= (1ULL << (63 - idx));
                this->board[idx] = PieceColor::White | PieceType::Rook;
                break;
            }
            case 'B': {
                int idx = this->get_square(x++, y);
                this->white_bishop_bitboard |= (1ULL << (63 - idx));
                this->board[idx] = PieceColor::White | PieceType::Bishop;
                break;
            }
            case 'N': {
                int idx = this->get_square(x++, y);
                this->white_knight_bitboard |= (1ULL << (63 - idx));
                this->board[idx] = PieceColor::White | PieceType::Knight;
                break;
            }
            case 'Q': {
                int idx = this->get_square(x++, y);
                this->white_queen_bitboard |= (1ULL << (63 - idx));
                this->board[idx] = PieceColor::White | PieceType::Queen;
                break;
            }
            case 'K': {
                int idx = this->get_square(x++, y);
                this->white_king_bitboard |= (1ULL << (63 - idx));
                this->board[idx] = PieceColor::White | PieceType::King;
                break;
            }
            case 'P': {
                int idx = this->get_square(x++, y);
                this->white_pawn_bitboard |= (1ULL << (63 - idx));
                this->board[idx] = PieceColor::White | PieceType::Pawn;
                break;
            }
            case ' ': {
                goto loop_end;
            }
            default: {
                char d = fen.at(i);
                if (std::isdigit(d)) {
                    x += d - '0';
                } else {
                    x++;
                    std::cerr << "Lol Invalid char at : " << i << "Char in question: " << d << std::endl;
                    exit(1);
                }
            }
        }
    }
loop_end:
    return;
}

void Game::draw_board() {
    bool w_b = true;
    Color white = GetColor(0xEBECD0FF);
    Color black = GetColor(0x739552ff);

    Color cursor_color = GetColor(0xffee80FF);
    Color selected_color = GetColor(0x8ab7ffFF);

    DrawText(this->b.get_turn() == White ? "White To Move" : "Black to Move", 10, 10, 20, BLACK);
    for (int i = 0; i < 64; i++) {
        int x = i % 8;
        int y = i / 8;



        if (this->cursor.x == x && this->cursor.y == y) {
            DrawRectangle(
                (x * this->square_size) + this->x, 
                (y * this->square_size) + this->y, 
                this->square_size, 
                this->square_size,
                cursor_color
            );
        } else if (this->selected_square.has_value() && this->selected_square.value().x == x && this->selected_square.value().y == y ){
            DrawRectangle(
                (x * this->square_size) + this->x, 
                (y * this->square_size) + this->y, 
                this->square_size, 
                this->square_size,
                selected_color
            );
        } else {
            DrawRectangle(
                (x * this->square_size) + this->x, 
                (y * this->square_size) + this->y, 
                this->square_size, 
                this->square_size,
                (w_b == true ? white : black)
            );
        }
        this->draw_piece(i);

        w_b = !w_b;
        if (x == 7) {
            w_b = !w_b;
        }
    }

    this->draw_debug();
}

void Board::toggle_turn() {
    this->is_white_turn = !this->is_white_turn;
}
#include <math.h>

// BUG: sometimes when the cursor is outside the board the game crashes
//
//NOTE: for some reason the cursor is selecting random pieces not defined in the board or values that should not be there in any cass
//
// TODO: Fix the bug
void Game::mouse_cursor() {
    Vector2 mouse = GetMousePosition();
    if (mouse.x < this->x || mouse.x > this->x + this->size || mouse.y < this->y || mouse.y > this->y + this->size) {
        return;
    }
    this->cursor.x = floor((mouse.x - this->x ) / this->square_size);
    this->cursor.y = floor((mouse.y - this->y ) / this->square_size);
}

void Game::select_piece() {
    // checks if std::optional is empty or not
    // if  not throws an error
    //
    // Get the coordinates of the cursor
    // checks if there is a piece or not

    if (this->selected_square.has_value()) {
        this->selected_square = std::nullopt;
    }
    assert(this->selected_square.has_value() == false && "Selected square is not empty");
    float x = this->cursor.x;
    float y = this->cursor.y;

    // check if the selected square has a piece
    uint16_t piece = this->b.get_piece_at_square(this->b.get_square(x, y));

    if (piece == 0) {
        return;
    }
    assert(piece != 0 && "No piece at the selected square");

    auto [color, type] = this->b.num_to_enum(piece);

    bool correct_turn = this->b.get_turn() == color;

    std::cout << "Turn: " << correct_turn << std::endl;
    if (!correct_turn) {
        std::cout << "Wrong turn" << std::endl;
        return;
    }

    std::cout << "Selected piece: " << piece << std::endl;

    this->selected_square = Vector2{x, y};
}

bool Board::move_piece(Vector2 old_pos, Vector2 new_pos) {
    // Get the piece at the old position
    // Get the piece at the new position

    int old_idx = this->get_square(old_pos.x, old_pos.y);
    int new_idx = this->get_square(new_pos.x, new_pos.y);

    uint16_t old_piece = this->get_piece_at_square(old_idx);
    uint16_t new_piece = this->get_piece_at_square(new_idx);

    if (old_piece == 0) { // No piece at the old position
        return false;
    }
    //NOTE: There is a piece at the new position, so we must destroy it if its an enemy piece;
    if (new_piece != 0) {
        // Check if the piece is an enemy piece
        if (this->num_to_enum(old_piece).first == this->num_to_enum(new_piece).first) {
            return false;
        } else {
            // Destroy the enemy piece
            uint64_t* bitboard = this->get_bitboard(new_piece);
            *bitboard &= ~(1ULL << (63 - new_idx));
        }
    }

    if (!this->is_playable_move(old_pos, new_pos)) {
        std::cout << "Not a playable move" << std::endl;
        return false;
    }


    // Update the bitboards
    //
    uint64_t* bitboard = this->get_bitboard(old_piece);
    // Cmagic to unset the bit at the old position and set the bit at the new position
    *bitboard &= ~(1ULL << (63 - old_idx));
    *bitboard |= (1ULL << (63 - new_idx));

    this->board[old_idx] = 0;
    this->board[new_idx] = old_piece;

    return true;
}

bool Board::is_playable_move(Vector2 start, Vector2 end) {
    Move x = {
        .start_pos = start,
        .end_pos = end,
    };
    std::cout << this->moves.size() << std::endl;
    for (auto move : this->moves) {

        // DEBUG:
        std::cout << "X start: " << x.start_pos.x << " " << x.start_pos.y << std::endl;
        std::cout << "X end: " << x.end_pos.x << " " << x.end_pos.y << std::endl;

        std::cout << "Move start: " << move.start_pos.x << " " << move.start_pos.y << std::endl;
        std::cout << "Move end: " << move.end_pos.x << " " << move.end_pos.y << std::endl;

        std::cout << "---------------------------------" << std::endl;

        if (move.is_eq(x)) {
            std::cout << "Move found" << std::endl;
            return true;
        } else {
            // std::cout << "Move not found" << std::endl;
            // // PRINT DEBUG:
            // std::cout << "Start: " << move.start_pos.x << " " << move.start_pos.y << std::endl;
            // std::cout << "End: " << move.end_pos.x << " " << move.end_pos.y << std::endl;
            //
            // std::cout << "---------------------------------" << std::endl;
            // std::cout << "Start: " << x.start_pos.x << " " << x.start_pos.y << std::endl;
            // std::cout << "End: " << x.end_pos.x << " " << x.end_pos.y << std::endl;
            //
            // std::cout << "----------Next--------------------" << std::endl;
        }
    }
    return false;
}

void Game::unselect_piece() {
    this->selected_square = std::nullopt;
}

void Game::move_piece() {
    if (this->b.move_piece(this->selected_square.value(), this->cursor) == true) {
        this->selected_square = std::nullopt;
        this->b.toggle_turn();
    }
}

void Game::move_cursor(int x, int y) {
    this->cursor.x += x;
    this->cursor.y += y;
}

uint16_t Board::get_piece_at_square(int idx) {
    // Get the idx and then check every bitboard to see if the piece is there
    // idfk if this is a good way to do it but it works :)
    return this->board[idx];
}

void Board::generate_moves() {
    // pseudo legal moves
    //
    // 1. Get the piece at the selected square
    //
    // NOTE: for the time being we will only generate moves for the pawns

    // Pawns can only move forward if there is not piece in front of them
    // they only move one square at a time unlsess they are at the starting position then they can move two squares
    // Theres also En-passant and promotion but we will get to that later

    // for (int i = 0; i < 8; i++) {
    // for (int j = 0; j < 8; j++) {
    //     uint16_t piece = this->board[i];
    //     if (piece == 0) {
    //         continue;
    //     }
    //     auto [color, type] = this->num_to_enum(piece);
    //     if (color != this->get_turn()) {
    //         continue;
    //     }
    //
    //     int y = i / 8;
    //     int x = i % 8;
    //
    //     Move move = {
    //         .start_pos = {.x = (float)x, .y = (float)y},
    //         .end_pos = {.x = (float)(x++), .y = (float)y }
    //     };
    //     this->moves.push_back(move);
    //
    //     if (this->is_pawn_starting_post(i, color)) {
    //         this->moves.push_back(move = {
    //             .start_pos = {.x = (float)x, .y = (float)y},
    //             .end_pos = {.x = (float)(x+2), .y = (float)y }
    //         });
    //     }
    // }

    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            uint16_t piece_int = this->board[this->get_square(x, y)];
            if (piece_int == 0) {
                continue;
            }
            Board::Piece p = this->num_to_enum_p(piece_int);
            if (p.color != this->get_turn()) {
                std::cout << "Wrong turn" << std::endl;
                continue;
            }
            std::cout << "Checking Moves for: " << x << " " << y << std::endl;
        }
    }
}


Board::Piece Board::num_to_enum_p(uint16_t pp) {
    int p = pp - 8;
    PieceColor color {};
    PieceType type = (PieceType) p;

    if (p < 0) {
        // White
        p += 8;
        color = White;
    } else {
        // Black
        color = Black;
    }
    return Piece {
        .color = color,
        .type = type
    };
}

bool Board::is_pawn_starting_post(int file, PieceColor color) {
    return color == White ? file == 1 : file == 6;
}


void Game::draw_piece(int i) {
    uint16_t piece = this->b.get_piece_at_square(i);
    if (piece == 0) {
        return;
    }
    Texture2D texture = this->texture_map[piece];
    int x = i % 8;
    int y = i / 8;
    DrawTexture(texture, x * this->square_size + this->x, y * this->square_size + this->y, WHITE);
}
