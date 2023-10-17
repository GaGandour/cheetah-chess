#include "chess_move.hpp"

#include <utility>
#include <vector>


// Implementations of ChessMove methods.
ChessMove::ChessMove(
        int old_x,
        int old_y,
        int new_x,
        int new_y,
        bool is_capture,
        bool is_castle,
        bool is_promotion,
        char promotion_piece,
        bool enables_en_passant
    ) :
    _old_x(old_x),
    _old_y(old_y),
    _new_x(new_x),
    _new_y(new_y),
    _is_capture(is_capture),
    _is_castle(is_castle),
    _enables_en_passant(enables_en_passant),
    _is_promotion(is_promotion),
    _promotion_piece(promotion_piece) {
        //TODO: Compute move hash.
        _move_hash = 0;
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
    return _is_castle;
}