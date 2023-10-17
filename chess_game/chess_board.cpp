#include "chess_move.hpp"
#include "chess_board.hpp"

#include <utility>
#include <iostream>

ChessBoard::ChessBoard() {
    _reset_board();
}

ChessBoard::ChessBoard(ChessBoard *previous_board, ChessMove *chess_move) {
    _white_turn = !previous_board->is_white_turn();
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; i++) {
            _chess_board[i][j] = previous_board->piece_at(i, j);
        }
    }

    std::pair<int, int> old_position = chess_move->get_old_position();
    std::pair<int, int> new_position = chess_move->get_new_position();

    _chess_board[new_position.first][new_position.second] = _chess_board[old_position.first][old_position.second];
    _chess_board[old_position.first][old_position.second] = ' ';

    _check_for_castle_rights(old_position);

    _num_moves = previous_board->get_num_moves() + 1;
    if (chess_move->is_capture()) {
        _num_moves_since_last_capture = 0;
    } else {
        _num_moves_since_last_capture = previous_board->get_num_moves_since_last_capture() + 1;
    }
    _board_hash = previous_board->_board_hash ^ chess_move->get_move_hash();
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

bool ChessBoard::is_occupied(int x, int y) {
    return piece_at(x, y) != ' ';
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