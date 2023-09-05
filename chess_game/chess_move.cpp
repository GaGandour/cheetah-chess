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
        _old_x = old_x;
        _old_y = old_y;
        _new_x = new_x;
        _new_y = new_y;

        _enables_en_passant = enables_en_passant;
        _is_promotion = is_promotion;
        _promotion_piece = promotion_piece;
        _is_capture = chess_board.piece_at(new_x, new_y) != ' ';
    }

    std::pair<int, int> ChessMove::get_old_position() {
        return std::make_pair(_old_x, _old_y);
    }
    std::pair<int, int> ChessMove::get_new_position() {
        return std::make_pair(_new_x, _new_y);
    }

    bool ChessMove::is_capture() {
        return _is_capture;
    }
}
