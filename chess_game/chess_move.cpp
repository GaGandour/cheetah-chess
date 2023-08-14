#include "chess.hpp"

#include <utility>
// #include <vector>
#include <iostream>

// Implementations of ChessMove methods.
namespace Chess {
    ChessMove::ChessMove(
            int old_x, 
            int old_y, 
            int new_x, 
            int new_y, 
            ChessBoard chess_board, 
            bool is_promotion = false, 
            char promotion_piece = ' ', 
            bool enables_en_passant = false
        ) {
        old_x_ = old_x;
        old_y_ = old_y;
        new_x_ = new_x;
        new_y_ = new_y;

        enables_en_passant_ = enables_en_passant;
        is_promotion_ = is_promotion;
        promotion_piece_ = promotion_piece;
        is_capture_ = chess_board.piece_at(new_x, new_y) != ' ';
    }

    std::pair<int, int> ChessMove::get_old_position() {
        return std::make_pair(old_x_, old_y_);
    }
    std::pair<int, int> ChessMove::get_new_position() {
        return std::make_pair(new_x_, new_y_);
    }

    bool ChessMove::is_capture() {
        return is_capture_;
    }
}
