#include "chess_move.hpp"

#include <utility>
#include <vector>



// Implementations of ChessMove methods.
ChessMove::ChessMove(
        ChessMoveParams params
    ) :
    _old_x(params.old_x),
    _old_y(params.old_y),
    _new_x(params.new_x),
    _new_y(params.new_y),

    _move_type(params.move_type),
    
    _is_promotion(params.is_promotion),
    _promotion_piece(params.promotion_piece),

    _moving_piece(params.moving_piece),
    _captured_piece(params.captured_piece),

    _enables_en_passant(params.enables_en_passant) {
        //TODO: Compute move hash.
        _move_hash = 0;
    }


std::pair<int, int> ChessMove::get_old_position() {
    return std::make_pair(_old_x, _old_y);
}

std::pair<int, int> ChessMove::get_new_position() {
    return std::make_pair(_new_x, _new_y);
}

MoveType ChessMove::get_move_type() {
    return _move_type;
}

bool ChessMove::is_capture() {
    return _move_type == MoveType::NORMAL_CAPTURE || MoveType::EN_PASSANT;
}


char ChessMove::get_moving_piece() {
    return _moving_piece;
}

char ChessMove::get_captured_piece() {
    return _captured_piece;
}

bool ChessMove::is_promotion() {
    return _is_promotion;
}

char ChessMove::get_promotion_piece() {
    return _promotion_piece;
}

bool ChessMove::enables_en_passant() {
    return _enables_en_passant;
}

long long ChessMove::get_move_hash() {
    return _move_hash;
}

bool ChessMove::is_castle() {
    return _move_type == MoveType::SMALL_CASTLE || _move_type == MoveType::BIG_CASTLE;
}
