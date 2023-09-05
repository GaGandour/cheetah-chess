#include "chess.hpp"

#include <utility>
// #include <vector>
#include <iostream>

// Implementation of ChessGame methods.
namespace Chess {
    ChessGame::ChessGame() {
        while (!_chess_board_stack.empty()) {
            _chess_board_stack.pop();
        }
        _chess_board_stack.push(ChessBoard());
    }

    std::vector<ChessMove> ChessGame::compute_legal_moves() {
        return _chess_board_stack.top().compute_legal_moves();
    }

    std::vector<ChessMove> ChessGame::compute_legal_moves(int x, int y) {
        return _chess_board_stack.top().compute_legal_moves(x, y);
    }

    void ChessGame::make_move(ChessMove chess_move) {
        _chess_board_stack.push(ChessBoard(_chess_board_stack.top(), chess_move));
    }

    void ChessGame::undo_move() {
        _chess_board_stack.pop();
    }

    void ChessGame::print_board() {
        _chess_board_stack.top().print_board();
    }

    bool ChessGame::is_check() {
        return _chess_board_stack.top().is_check();
    }



}