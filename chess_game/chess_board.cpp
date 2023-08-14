#include "chess.hpp"

#include <utility>
// #include <vector>
#include <iostream>

// Implementations of ChessBoard methods.
namespace Chess {
    ChessBoard::ChessBoard() {
        reset_board_();
    }

    ChessBoard::ChessBoard(ChessBoard previous_board, ChessMove chess_move) {
        white_turn_ = !previous_board.white_turn_;
        std::pair<int, int> old_position = chess_move.get_old_position();
        std::pair<int, int> new_position = chess_move.get_new_position();
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; i++) {
                chess_board_[i][j] = previous_board.piece_at(i, j);
            }
        }

        chess_board_[new_position.first][new_position.second] = chess_board_[old_position.first][old_position.second];
        chess_board_[old_position.first][old_position.second] = ' ';
        num_moves_ = previous_board.num_moves_ + 1;
        
        if (chess_move.is_capture()) {
            num_moves_since_capture_ = 0;
        } else {
            num_moves_since_capture_ = previous_board.num_moves_since_capture_ + 1;
        }
    }

    char ChessBoard::piece_at(int x, int y) {
        if (x < 0 || x > 7 || y < 0 || y > 7) {
            return ' ';
        }
        return chess_board_[x][y];
    }

    void ChessBoard::reset_board_() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; i++) {
                chess_board_[i][j] = INITIAL_CHESS_BOARD[i][j];
            }
        }
        white_turn_ = true;
        num_moves_ = 0;
        num_moves_since_capture_ = 0;
        can_black_big_castle_ = true;
        can_black_small_castle_ = true;
        can_white_big_castle_ = true;
        can_white_small_castle_ = true;
    }

    void ChessBoard::print_board() {
        for (int i = 0; i < 8; i++) {
            std::cout << "-----------------" << std::endl;
            for (int j = 0; j < 8; j++) {
                std::cout << "| " << chess_board_[i][j] << " ";
            }
            std::cout << "|" << std::endl;
        }
        std::cout << "-----------------" << std::endl;
    }

    bool ChessBoard::is_white_turn() {
        return white_turn_;
    }

    long long ChessBoard::get_board_hash() {
        return board_hash_;
    }
}

