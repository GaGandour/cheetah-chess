#include "chess_piece.hpp"
#include "chess_board.hpp"

#include <utility>
// #include <vector>
#include <iostream>
#include <algorithm>

std::vector<ChessMove> ChessPiece::compute_possible_moves_disregarding_check(std::pair<int, int> &position, ChessBoard *chess_board) {
    std::vector<std::pair<int, int>> attacked_squares;
    compute_attacked_squares(position, chess_board, attacked_squares);
    std::vector<ChessMove> moves = {};

    for (std::pair<int, int> attacked_square : attacked_squares) {
        moves.push_back(
            ChessMove(
                position.first, 
                position.second, 
                attacked_square.first, 
                attacked_square.second
            )
        );
    }
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
    std::vector<std::pair<int, int>> attacked_squares = {};
    compute_attacked_squares(position, chess_board, attacked_squares);
    std::vector<ChessMove> moves = {};

    for (std::pair<int, int> attacked_square : attacked_squares) {
        moves.push_back(
            ChessMove(
                position.first, 
                position.second, 
                attacked_square.first, 
                attacked_square.second
            )
        );
    }

    _compute_and_push_castle_moves(position, chess_board, moves);
}

void King::_compute_and_push_castle_moves(std::pair<int, int> &position, ChessBoard *chess_board, std::vector<ChessMove> moves) {
    //TODO: everything!
    if (chess_board->is_white_turn()) {
        //TODO: white
        if (chess_board->can_white_big_castle()) {
            // if ()
            // moves.push_back
        }
        if (chess_board->can_white_small_castle()) {

        }
    } else {
        //TODO: black
    }
}


void Queen::compute_attacked_squares(std::pair<int, int> &position, ChessBoard *chess_board, std::vector<std::pair<int, int>> &attacked_squares) {
    ChessPiece* aux_piece = new Bishop();
    aux_piece->compute_attacked_squares(position, chess_board, attacked_squares);
    delete aux_piece;

    aux_piece = new Rook();
    aux_piece->compute_attacked_squares(position, chess_board, attacked_squares);
    delete aux_piece;
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

    if (is_valid_coordinate(new_x, y - 1))
        attacked_squares.push_back(std::make_pair(new_x, y - 1));
    if (is_valid_coordinate(new_x, y + 1))
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
                    ChessMove(
                        position.first, 
                        position.second, 
                        new_x, 
                        new_y,
                        false,
                        false,
                        true,
                        promotion_piece
                    )
                );
            }
        } else {
            moves.push_back(
                ChessMove(
                    position.first, 
                    position.second, 
                    new_x, 
                    new_y
                )
            );
        }
    }

    // handle double jump
    if (position.first == WPAWNROW || position.first == BPAWNROW) {
        new_x = position.first + 2 * row_offset;
        new_y = position.second;
        if (!is_valid_coordinate(new_x, new_y)) {

        } else if (chess_board->is_occupied(new_x, new_y)) {

        } else if (chess_board->is_occupied(new_x - row_offset, new_y)) {

        }
        else {
            moves.push_back(
                ChessMove(
                    position.first, 
                    position.second, 
                    new_x, 
                    new_y,
                    false,
                    false,
                    false,
                    ' ',
                    true
                )
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
                        ChessMove(
                            position.first, 
                            position.second, 
                            new_x, 
                            new_y,
                            true,
                            false,
                            true,
                            promotion_piece
                        )
                    );
                }
            } else {
                moves.push_back(
                    ChessMove(
                        position.first, 
                        position.second, 
                        new_x, 
                        new_y,
                        true
                    )
                );
            }
        }
    }

    //TODO: handle en passant
}