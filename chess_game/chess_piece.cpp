#include "chess_piece.hpp"
#include "chess_board.hpp"

#include <utility>
#include <vector>
#include <iostream>
#include <algorithm>

std::vector<ChessMove> ChessPiece::compute_possible_moves_disregarding_check(std::pair<int, int> &position, ChessBoard *chess_board) {
    std::vector<std::pair<int, int>> attacked_squares;
    compute_attacked_squares(position, chess_board, attacked_squares);
    std::vector<ChessMove> moves = {};
    
    MoveType move_type;
    bool is_capture;
    char captured_piece;


    for (std::pair<int, int> attacked_square : attacked_squares) {
        is_capture = chess_board->is_occupied(attacked_square);
        move_type = is_capture ? MoveType::NORMAL_CAPTURE : MoveType::NORMAL;
        captured_piece = chess_board->piece_at(attacked_square);
        moves.push_back(
            ChessMove({
                .old_x = position.first,
                .old_y = position.second,
                .new_x = attacked_square.first,
                .new_y = attacked_square.second,
                .is_white_moving = chess_board->is_white_turn(),
                .move_type = move_type,
                .moving_piece = _piece_code,
                .captured_piece = captured_piece
            })
        );
    }

    return moves;
}

void King::compute_attacked_squares(std::pair<int, int> &position, ChessBoard *chess_board, std::vector<std::pair<int, int>> &attacked_squares) {
    static const std::vector<std::pair<int, int>> king_movements_offsets = {
        { 0, -1},
        { 0,  1},
        { 1, -1},
        { 1,  0},
        { 1,  1},
        {-1, -1},
        {-1,  0},
        {-1,  1},
    };

    int new_x, new_y;
    for (std::pair<int, int> offset : king_movements_offsets) {
        new_x = position.first + offset.first;
        new_y = position.second + offset.second;

        if (!is_valid_coordinate(new_x, new_y))
            continue;

        if (!belong_to_same_player(chess_board->piece_at(new_x, new_y), _piece_code))
            attacked_squares.push_back(std::make_pair(new_x, new_y));
    }
}

std::vector<ChessMove> King::compute_possible_moves_disregarding_check(std::pair<int, int> &position, ChessBoard *chess_board) {
    std::vector<ChessMove> moves = ChessPiece::compute_possible_moves_disregarding_check(position, chess_board);

    _compute_and_push_castle_moves(position, chess_board, moves);
}

void King::_compute_and_push_castle_moves(std::pair<int, int> &position, ChessBoard *chess_board, std::vector<ChessMove> moves) {
    bool test_big_castle = false;
    test_big_castle = test_big_castle || (chess_board->is_white_turn() && chess_board->can_white_big_castle());
    test_big_castle = test_big_castle || (chess_board->is_black_turn() && chess_board->can_black_big_castle());

    if (test_big_castle) {
        _validate_and_push_castle_move(chess_board, moves, true);
    }

    bool test_small_castle = false;
    test_small_castle = test_small_castle || (chess_board->is_white_turn() && chess_board->can_white_small_castle());
    test_small_castle = test_small_castle || (chess_board->is_black_turn() && chess_board->can_black_small_castle());
    if (test_small_castle) {
        _validate_and_push_castle_move(chess_board, moves, false);
    }
}

void King::_validate_and_push_castle_move(ChessBoard *chess_board, std::vector<ChessMove> moves, bool is_big_castle) {
    std::vector<std::pair<int, int>> castle_inner_squares;
    int castle_row = is_white() ? WROW : BROW;
    int castle_col = is_big_castle ? KING_AFTER_BIG_CASTLE_COL : KING_AFTER_SMALL_CASTLE_COL;

    if (is_white()){
        castle_inner_squares = is_big_castle ? WBIG_CASTLE_INNER_SQUARES : WSMALL_CASTLE_INNER_SQUARES;
    } else {
        castle_inner_squares = is_big_castle ? BBIG_CASTLE_INNER_SQUARES : BSMALL_CASTLE_INNER_SQUARES;
    }

    for (auto square : castle_inner_squares) {
        if (chess_board->is_occupied(square))
            return;
    }
    moves.push_back(ChessMove({
        .old_x = castle_row,
        .old_y = KING_COL,
        .new_x = castle_row,
        .new_y = castle_col,
        .is_white_moving = is_white(),
        .move_type = is_big_castle ? MoveType::BIG_CASTLE : MoveType::SMALL_CASTLE,
        .moving_piece = _piece_code,
    }));
}

void Queen::compute_attacked_squares(std::pair<int, int> &position, ChessBoard *chess_board, std::vector<std::pair<int, int>> &attacked_squares) {
    ChessPiece* bishop_aux_piece;
    ChessPiece* rook_aux_piece;

    if (is_white()) {
        bishop_aux_piece = new WBishop();
        rook_aux_piece = new WRook();
    } else {
        bishop_aux_piece = new BBishop();
        rook_aux_piece = new BRook();
    }

    bishop_aux_piece->compute_attacked_squares(position, chess_board, attacked_squares);
    rook_aux_piece->compute_attacked_squares(position, chess_board, attacked_squares);

    delete bishop_aux_piece;
    delete rook_aux_piece;
}

void Rook::compute_attacked_squares(std::pair<int, int> &position, ChessBoard *chess_board, std::vector<std::pair<int, int>> &attacked_squares) {
    int i = 0, x = position.first, y = position.second;
    while (is_valid_coordinate(x + i, y) && !belong_to_same_player(chess_board->piece_at(x + i, y), _piece_code)) {
        attacked_squares.push_back(std::make_pair(x + i, y));
        if (chess_board->is_occupied(x + i, y))
            break;
        ++i;
    }
    i = 0;
    while (is_valid_coordinate(x - i, y) && !belong_to_same_player(chess_board->piece_at(x - i, y), _piece_code)) {
        attacked_squares.push_back(std::make_pair(x - i, y));
        if (chess_board->is_occupied(x - i, y))
            break;
        ++i;
    }
    i = 0;
    while (is_valid_coordinate(x, y + i) && !belong_to_same_player(chess_board->piece_at(x, y + i), _piece_code)) {
        attacked_squares.push_back(std::make_pair(x, y + i));
        if (chess_board->is_occupied(x, y + i))
            break;
        ++i;
    }
    i = 0;
    while (is_valid_coordinate(x, y - i) && !belong_to_same_player(chess_board->piece_at(x, y - i), _piece_code)) {
        attacked_squares.push_back(std::make_pair(x, y - i));
        if (chess_board->is_occupied(x, y - i))
            break;
        ++i;
    }
}


void Bishop::compute_attacked_squares(std::pair<int, int> &position, ChessBoard *chess_board, std::vector<std::pair<int, int>> &attacked_squares) {
    int i = 0, x = position.first, y = position.second;
    while (is_valid_coordinate(x + i, y + i) && !belong_to_same_player(chess_board->piece_at(x + i, y + i), _piece_code)) {
        attacked_squares.push_back(std::make_pair(x + i, y + i));
        if (chess_board->is_occupied(x + i, y + i))
            break;
        ++i;
    }
    i = 0;
    while (is_valid_coordinate(x - i, y + i) && !belong_to_same_player(chess_board->piece_at(x - i, y + i), _piece_code)) {
        attacked_squares.push_back(std::make_pair(x - i, y + i));
        if (chess_board->is_occupied(x - i, y + i))
            break;
        ++i;
    }
    i = 0;
    while (is_valid_coordinate(x + i, y - i) && !belong_to_same_player(chess_board->piece_at(x + i, y - i), _piece_code)) {
        attacked_squares.push_back(std::make_pair(x + i, y - i));
        if (chess_board->is_occupied(x + i, y - i))
            break;
        ++i;
    }
    i = 0;
    while (is_valid_coordinate(x - i, y - i) && !belong_to_same_player(chess_board->piece_at(x - i, y - i), _piece_code)) {
        attacked_squares.push_back(std::make_pair(x - i, y - i));
        if (chess_board->is_occupied(x - i, y - i))
            break;
        ++i;
    }
}

void Knight::compute_attacked_squares(std::pair<int, int> &position, ChessBoard *chess_board, std::vector<std::pair<int, int>> &attacked_squares) {
    static const std::vector<std::pair<int, int>> knight_movements_offsets = {
        { 2,  1},
        { 2, -1},
        {-2,  1},
        {-2, -1},
        { 1,  2},
        { 1, -2},
        {-1,  2},
        {-1, -2},
    };

    int new_x, new_y;
    for (std::pair<int, int> offset : knight_movements_offsets) {
        new_x = position.first + offset.first;
        new_y = position.second + offset.second;

        if (!is_valid_coordinate(new_x, new_y))
            continue;

        if (!belong_to_same_player(chess_board->piece_at(new_x, new_y), _piece_code))
            attacked_squares.push_back(std::make_pair(new_x, new_y));
    }
}

void Pawn::compute_attacked_squares(std::pair<int, int> &position, ChessBoard *chess_board, std::vector<std::pair<int, int>> &attacked_squares) {
    int new_x, y;
    y = position.second;

    int row_offset = is_white() ? -1 : 1;
    new_x = position.first + row_offset;

    if (is_valid_coordinate(new_x, y - 1) && !belong_to_same_player(chess_board->piece_at(new_x, y - 1), _piece_code))
        attacked_squares.push_back(std::make_pair(new_x, y - 1));
    if (is_valid_coordinate(new_x, y + 1) && !belong_to_same_player(chess_board->piece_at(new_x, y + 1), _piece_code))
        attacked_squares.push_back(std::make_pair(new_x, y + 1));
}

std::vector<ChessMove> Pawn::compute_possible_moves_disregarding_check(std::pair<int, int> &position, ChessBoard *chess_board) {
    //TODO: DO
    int row_offset = is_white() ? -1 : 1;
    int new_x = position.first + row_offset;
    int new_y = position.second;

    std::vector<ChessMove> moves = {};
    
    std::vector<char> possible_promotions;
    if (is_white()) {
        possible_promotions = {
            WQUEEN, WBISHOP, WKNIGHT, WROOK
        };
    } else {
        possible_promotions = {
            BQUEEN, BBISHOP, BKNIGHT, BROOK
        };  
    } 
    
    // first, check if can move one square forward
    if (is_valid_coordinate(new_x, new_y) && !chess_board->is_occupied(new_x, new_y)) {
        if (new_x == WROW || new_x == BROW) {
            // if is a promotion
            for (char promotion_piece : possible_promotions) {
                moves.push_back(
                    ChessMove({
                        .old_x = position.first, 
                        .old_y = position.second, 
                        .new_x = new_x, 
                        .new_y = new_y,
                        .is_white_moving = is_white(),
                        .is_promotion = true,
                        .promotion_piece = promotion_piece,
                        .moving_piece = _piece_code
                    })
                );
            }
        } else {
            moves.push_back(
                ChessMove({
                    .old_x = position.first, 
                    .old_y = position.second, 
                    .new_x = new_x, 
                    .new_y = new_y,
                    .is_white_moving = is_white(),
                    .moving_piece = _piece_code
                })
            );
        }
    }

    // handle double jump
    if (position.first == WPAWN_ROW || position.first == BPAWN_ROW) {
        new_x = position.first + 2 * row_offset;
        new_y = position.second;
        if (!is_valid_coordinate(new_x, new_y)) {

        } else if (chess_board->is_occupied(new_x, new_y)) {

        } else if (chess_board->is_occupied(new_x - row_offset, new_y)) {

        }
        else {
            moves.push_back(
                ChessMove({
                    .old_x = position.first, 
                    .old_y = position.second, 
                    .new_x = new_x, 
                    .new_y = new_y,
                    .is_white_moving = is_white(),
                    .moving_piece = _piece_code,
                    .enables_en_passant = true
                })
            );
        }
    }

    // handle captures
    static const std::vector<int> column_offsets = {-1, 1};
    for (int delta_y : column_offsets) {
        new_x = position.first + row_offset;
        new_y = position.second + delta_y;
        if (
            is_valid_coordinate(new_x, new_y) && 
            chess_board->is_occupied(new_x, new_y) && 
            !belong_to_same_player(chess_board->piece_at(new_x, new_y), _piece_code)
        ) {
            if (new_x == WROW || new_x == BROW) {
                // if is a promotion
                for (char promotion_piece : possible_promotions) {
                    moves.push_back(
                        ChessMove({
                            .old_x = position.first, 
                            .old_y = position.second, 
                            .new_x = new_x, 
                            .new_y = new_y,
                            .is_white_moving = is_white(),
                            .move_type = MoveType::NORMAL_CAPTURE,
                            .is_promotion = true,
                            .promotion_piece = promotion_piece,
                            .moving_piece = _piece_code,
                            .captured_piece = chess_board->piece_at(new_x, new_y)
                        })
                    );
                }
            } else {
                moves.push_back(
                    ChessMove({
                        .old_x = position.first, 
                        .old_y = position.second, 
                        .new_x = new_x, 
                        .new_y = new_y,
                        .is_white_moving = is_white(),
                        .move_type = MoveType::NORMAL_CAPTURE,
                        .moving_piece = _piece_code,
                        .captured_piece = chess_board->piece_at(new_x, new_y)
                    })
                );
            }
        }
    }

    // handle en passant
    if (chess_board->is_en_passant_enabled()) {
        std::pair<int, int> en_passant_square = chess_board->get_en_passant_square();
        if (
            en_passant_square.first == position.first && 
            std::abs(en_passant_square.second - position.second) == 1
        ) {
            moves.push_back(
                ChessMove({
                    .old_x = position.first, 
                    .old_y = position.second, 
                    .new_x = position.first + row_offset, 
                    .new_y = en_passant_square.second,
                    .is_white_moving = is_white(),
                    .move_type = MoveType::EN_PASSANT,
                    .moving_piece = _piece_code,
                    .captured_piece = chess_board->piece_at(en_passant_square)
                })
            );
        }
    }
}