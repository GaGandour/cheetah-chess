#include "chess_move.hpp"
#include "chess_board.hpp"

#include <utility>
#include <iostream>

ChessBoard::ChessBoard() {
    _reset_board();
}

ChessBoard::ChessBoard(ChessBoard *previous_board, ChessMove *chess_move) {
    // change turns
    _white_turn = !previous_board->is_white_turn();
    // copy board
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; i++) {
            _chess_board[i][j] = previous_board->piece_at(i, j);
        }
    }
    // copy num pieces
    _num_pieces = previous_board->_num_pieces;

    // get positions involved
    std::pair<int, int> old_position = chess_move->get_old_position();
    std::pair<int, int> new_position = chess_move->get_new_position();
    // make move for moving piece
    _set_piece_at(old_position, ' ');
    _set_piece_at(new_position, chess_move->get_moving_piece());
    
    // if promotion, change piece
    if (chess_move->is_promotion()) {
        --_num_pieces[chess_move->get_moving_piece()];
        _set_piece_at(new_position, chess_move->get_promotion_piece());
        ++_num_pieces[chess_move->get_promotion_piece()];
    }

    // remove piece in en passant
    if (chess_move->get_move_type() == MoveType::EN_PASSANT) {
        std::pair<int, int> en_passant_square = previous_board->get_en_passant_square();
        --_num_pieces[previous_board->piece_at(en_passant_square)];
        _set_piece_at(en_passant_square, ' ');
    }
    
    // extra move for castling
    if (chess_move->is_castle()) {
        std::pair<int, int> rook_square;
        std::pair<int, int> rook_square_after_castle;
        char rook_piece;

        // get columns involved in rook movement
        if (chess_move->get_move_type() == MoveType::BIG_CASTLE) {
            rook_square.second = LEFT_WROOK_SQUARE.second;
            rook_square_after_castle.second = LEFT_WROOK_SQUARE_AFTER_CASTLE.second;
        } else {
            rook_square.second = RIGHT_WROOK_SQUARE.second;
            rook_square_after_castle.second = RIGHT_WROOK_SQUARE_AFTER_CASTLE.second;
        }

        // get rows involved in rook movement, and piece code
        // also, revoke castle rights.
        if (previous_board->is_white_turn()) {
            rook_square.first = LEFT_WROOK_SQUARE.first;
            rook_square_after_castle.first = LEFT_WROOK_SQUARE_AFTER_CASTLE.first;
            rook_piece = WROOK;
            _can_white_big_castle = false;
            _can_white_small_castle = false;
        } else {
            rook_square.first = LEFT_BROOK_SQUARE.first;
            rook_square_after_castle.first = LEFT_BROOK_SQUARE_AFTER_CASTLE.first;
            rook_piece = BROOK;
            _can_black_big_castle = false;
            _can_black_small_castle = false;
        }

        // move rook
        _chess_board[rook_square.first][rook_square.second] = ' ';
        _chess_board[rook_square_after_castle.first][rook_square_after_castle.second] = rook_piece;
    }

    // remove castle rights if rook or king moved
    _check_for_castle_rights(old_position);

    // set move counters
    _num_moves = previous_board->get_num_moves() + 1;
    if (chess_move->is_capture()) {
        _num_moves_since_last_capture = 0;
    } else {
        _num_moves_since_last_capture = previous_board->get_num_moves_since_last_capture() + 1;
    }

    // set en passant
    if (chess_move->enables_en_passant()) {
        _en_passant_enabled = true;
        _en_passant_square = new_position;
    } else {
        _en_passant_enabled = false;
    }

    _board_hash = previous_board->get_board_hash() ^ chess_move->get_move_hash();
}

void ChessBoard::_check_for_castle_rights(std::pair<int, int> &old_position) {
    if (old_position == WKING_SQUARE) {
        _can_white_big_castle = false;
        _can_white_small_castle = false;
        return;
    }
    if (old_position == BKING_SQUARE) {
        _can_black_big_castle = false;
        _can_black_small_castle = false;
        return;
    }
    if (old_position == LEFT_WROOK_SQUARE) {
        _can_white_big_castle = false;
        return;
    }
    if (old_position == LEFT_BROOK_SQUARE) {
        _can_black_big_castle = false;
        return;
    }
    if (old_position == RIGHT_WROOK_SQUARE) {
        _can_white_small_castle = false;
        return;
    }
    if (old_position == RIGHT_BROOK_SQUARE) {
        _can_black_small_castle = false;
        return;
    }
}

char ChessBoard::piece_at(int x, int y) {
    if (!is_valid_coordinate(x, y)) {
        return ' ';
    }
    return _chess_board[x][y];
}

char ChessBoard::piece_at(std::pair<int, int> &position) {
    return piece_at(position.first, position.second);
}

bool ChessBoard::is_occupied(int x, int y) {
    return piece_at(x, y) != ' ';
}

bool ChessBoard::is_occupied(std::pair<int, int> &position) {
    return is_occupied(position.first, position.second);
}

void ChessBoard::_reset_board() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; i++) {
            _chess_board[i][j] = INITIAL_CHESS_BOARD[i][j];
        }
    }
    _white_turn = true;
    _num_moves = 0;
    _num_moves_since_last_capture = 0;
    _can_black_big_castle = true;
    _can_black_small_castle = true;
    _can_white_big_castle = true;
    _can_white_small_castle = true;

    _num_pieces[WKING] = 1;
    _num_pieces[BKING] = 1;
    _num_pieces[WQUEEN] = 1;
    _num_pieces[BQUEEN] = 1;
    _num_pieces[WROOK] = 2;
    _num_pieces[BROOK] = 2;
    _num_pieces[WBISHOP] = 2;
    _num_pieces[BBISHOP] = 2;
    _num_pieces[WKNIGHT] = 2;
    _num_pieces[BKNIGHT] = 2;
    _num_pieces[WPAWN] = 8;
    _num_pieces[BPAWN] = 8;
}

void ChessBoard::_set_piece_at(int x, int y, char piece) {
    if (!is_valid_coordinate(x, y)) {
        return;
    }
    _chess_board[x][y] = piece;
}

void ChessBoard::_set_piece_at(std::pair<int, int> &position, char piece) {
    int x = position.first;
    int y = position.second;
    if (!is_valid_coordinate(x, y)) {
        return;
    }
    _chess_board[x][y] = piece;
}

void ChessBoard::print_board() {
    for (int i = 0; i < 8; i++) {
        std::cout << "-----------------" << std::endl;
        for (int j = 0; j < 8; j++) {
            std::cout << "| " << _chess_board[i][j] << " ";
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "-----------------" << std::endl;
}

bool ChessBoard::is_white_turn() {
    return _white_turn;
}

bool ChessBoard::is_black_turn() {
    return !_white_turn;
}

long long ChessBoard::get_board_hash() {
    return _board_hash;
}

int ChessBoard::get_num_moves() {
    return _num_moves;
}

int ChessBoard::get_num_moves_since_last_capture() {
    return _num_moves_since_last_capture;
}

bool ChessBoard::can_white_big_castle() {
    return _can_white_big_castle;
}
bool ChessBoard::can_white_small_castle() {
    return _can_white_small_castle;
}
bool ChessBoard::can_black_big_castle() {
    return _can_black_big_castle;
}
bool ChessBoard::can_black_small_castle() {
    return _can_black_small_castle;
};


bool ChessBoard::is_en_passant_enabled() {
    return _en_passant_enabled;
}

std::pair<int, int> ChessBoard::get_en_passant_square() {
    return _en_passant_square;
}