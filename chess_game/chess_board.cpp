#include "chess.hpp"

#include <utility>
// #include <vector>
#include <iostream>

// Implementations of ChessBoard methods.
namespace Chess {
    ChessBoard::ChessBoard() {
        _reset_board();
    }

    ChessBoard::ChessBoard(ChessBoard previous_board, ChessMove chess_move) {
        _white_turn = !previous_board._white_turn;
        std::pair<int, int> old_position = chess_move.get_old_position();
        std::pair<int, int> new_position = chess_move.get_new_position();
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; i++) {
                _chess_board[i][j] = previous_board.piece_at(i, j);
            }
        }

        _chess_board[new_position.first][new_position.second] = _chess_board[old_position.first][old_position.second];
        _chess_board[old_position.first][old_position.second] = ' ';
        _num_moves = previous_board._num_moves + 1;
        
        if (chess_move.is_capture()) {
            _num_moves_since_capture = 0;
        } else {
            _num_moves_since_capture = previous_board._num_moves_since_capture + 1;
        }
    }

    char ChessBoard::piece_at(int x, int y) {
        if (x < 0 || x > 7 || y < 0 || y > 7) {
            return ' ';
        }
        return _chess_board[x][y];
    }

    void ChessBoard::_reset_board() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; i++) {
                _chess_board[i][j] = INITIAL_CHESS_BOARD[i][j];
            }
        }
        _white_turn = true;
        _num_moves = 0;
        _num_moves_since_capture = 0;
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
}

