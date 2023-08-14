#include "chess.hpp"

#include <utility>
// #include <vector>
#include <iostream>

// Implementation of ChessGame methods.
namespace Chess {
    ChessGame::ChessGame() {
        while (!chess_board_stack_.empty()) {
            chess_board_stack_.pop();
        }
        chess_board_stack_.push(ChessBoard());
    }

    std::vector<ChessMove> ChessGame::compute_legal_moves() {
        return chess_board_stack_.top().compute_legal_moves();
    }

    std::vector<ChessMove> ChessGame::compute_legal_moves(int x, int y) {
        return chess_board_stack_.top().compute_legal_moves(x, y);
    }

    void ChessGame::make_move(ChessMove chess_move) {
        chess_board_stack_.push(ChessBoard(chess_board_stack_.top(), chess_move));
    }

    void ChessGame::undo_move() {
        chess_board_stack_.pop();
    }

    void ChessGame::print_board() {
        chess_board_stack_.top().print_board();
    }

    bool ChessGame::is_check() {
        return chess_board_stack_.top().is_check();
    }



}