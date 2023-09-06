#include "chess.hpp"

#include <utility>
// #include <vector>
#include <iostream>
#include <algorithm>

// Implementations of ChessPiece methods.
namespace Chess {
    ChessPiece::ChessPiece(int x, int y, ChessBoard *chess_board) {
        _piece = chess_board->piece_at(x, y);
        _x = x;
        _y = y;
        _chess_board = chess_board;
    }

    bool ChessPiece::_belong_to_same_player(char piece1, char piece2) {
        if (piece1 == ' ' || piece2 == ' ') {
            return false;
        }
        char difference = piece1 - piece2;
        if (difference < 26 && difference > -26) {
            return true;
        }
        return false;
    }

    bool ChessPiece::_belong_to_different_players(char piece1, char piece2) {
        if (piece1 == ' ' || piece2 == ' ') {
            return false;
        }
        char difference = piece1 - piece2;
        if (difference < 26 && difference > -26) {
            return false;
        }
        return true;
    }

    void ChessPiece::_push_coordinates_to_square_vector(std::vector<std::pair<int,int>> &attacked_squares, int x, int y) {
        if (!_is_valid_coordinate(x, y))
            return;
        attacked_squares.push_back(std::make_pair(x, y));
    }

    void ChessPiece::_compute_rook_attacked_squares(std::vector<std::pair<int,int>> &attacked_squares) {
        int i = 0;
        while (_is_valid_coordinate(_x + i, _y) && !_belong_to_same_player(_chess_board->piece_at(_x + i, _y), _piece)) {
            _push_coordinates_to_square_vector(attacked_squares, _x + i, _y);
            if (_chess_board->is_occupied(_x + i, _y)) // can't jump squares
                break;
            i++;
        }
        i = 0;
        while (_is_valid_coordinate(_x - i, _y) && !_belong_to_same_player(_chess_board->piece_at(_x - i, _y), _piece)) {
            _push_coordinates_to_square_vector(attacked_squares, _x - i, _y);
            if (_chess_board->is_occupied(_x - i, _y)) // can't jump squares
                break;
            i++;
        }
        i = 0;
        while (_is_valid_coordinate(_x, _y + i) && !_belong_to_same_player(_chess_board->piece_at(_x, _y + i), _piece)) {
            _push_coordinates_to_square_vector(attacked_squares, _x, _y + i);
            if (_chess_board->is_occupied(_x, _y + i)) // can't jump squares
                break;
            i++;
        }
        i = 0;
        while (_is_valid_coordinate(_x, _y - i) && !_belong_to_same_player(_chess_board->piece_at(_x, _y - i), _piece)) {
            _push_coordinates_to_square_vector(attacked_squares, _x, _y - i);
            if (_chess_board->is_occupied(_x, _y - i)) // can't jump squares
                break;
            i++;
        }
    }


    void ChessPiece::_compute_bishop_attacked_squares(std::vector<std::pair<int,int>> &attacked_squares) {
        int i = 0;
        while (_is_valid_coordinate(_x + i, _y + i) && !_belong_to_same_player(_chess_board->piece_at(_x + i, _y + i), _piece)) {
            _push_coordinates_to_square_vector(attacked_squares, _x + i, _y + i);
            if (_chess_board->is_occupied(_x + i, _y + i)) // can't jump squares
                break;
            i++;
        }
        i = 0;
        while (_is_valid_coordinate(_x - i, _y + i) && !_belong_to_same_player(_chess_board->piece_at(_x - i, _y + i), _piece)) {
            _push_coordinates_to_square_vector(attacked_squares, _x - i, _y + i);
            if (_chess_board->is_occupied(_x - i, _y + i)) // can't jump squares
                break;
            i++;
        }
        i = 0;
        while (_is_valid_coordinate(_x + i, _y - i) && !_belong_to_same_player(_chess_board->piece_at(_x + i, _y - i), _piece)) {
            _push_coordinates_to_square_vector(attacked_squares, _x + i, _y - i);
            if (_chess_board->is_occupied(_x + i, _y - i)) // can't jump squares
                break;
            i++;
        }
        i = 0;
        while (_is_valid_coordinate(_x - i, _y - i) && !_belong_to_same_player(_chess_board->piece_at(_x - i, _y - i), _piece)) {
            _push_coordinates_to_square_vector(attacked_squares, _x - i, _y - i);
            if (_chess_board->is_occupied(_x - i, _y - i)) // can't jump squares
                break;
            i++;
        }
    }

    void ChessPiece::_compute_queen_attacked_squares(std::vector<std::pair<int,int>> &attacked_squares) {
        _compute_rook_attacked_squares(attacked_squares);
        _compute_bishop_attacked_squares(attacked_squares);
    }

    void ChessPiece::_compute_knight_attacked_squares(std::vector<std::pair<int,int>> &attacked_squares) {
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
            new_x = _x + offset.first;
            new_y = _y + offset.second;

            if (!_belong_to_same_player(_chess_board->piece_at(new_x, new_y), _piece))
                _push_coordinates_to_square_vector(attacked_squares, new_x, new_y);
        }
    }

    void ChessPiece::_compute_king_attacked_squares(std::vector<std::pair<int,int>> &attacked_squares) {
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
            new_x = _x + offset.first;
            new_y = _y + offset.second;

            if (!_belong_to_same_player(_chess_board->piece_at(new_x, new_y), _piece))
                _push_coordinates_to_square_vector(attacked_squares, new_x, new_y);
        }
    }

    std::vector<std::pair<int, int>> ChessPiece::compute_attacked_squares() {
        std::vector<std::pair<int, int>> attacked_squares;
        switch (_piece)
        {
        case 'n':
        case 'N':
            _compute_knight_attacked_squares(attacked_squares);
            break;
        case 'r':
        case 'R':
            _compute_rook_attacked_squares(attacked_squares);
            break;
        case 'b':
        case 'B':
            _compute_bishop_attacked_squares(attacked_squares);
            break;
        case 'q':
        case 'Q':
            _compute_queen_attacked_squares(attacked_squares);
            break;
        case 'k':
        case 'K':
            _compute_king_attacked_squares(attacked_squares);
            break;
        case 'p':
            attacked_squares.push_back(std::make_pair(_x + 1, _y + 1));
            attacked_squares.push_back(std::make_pair(_x + 1, _y - 1));
            break;
        case 'P':
            attacked_squares.push_back(std::make_pair(_x - 1, _y + 1));
            attacked_squares.push_back(std::make_pair(_x - 1, _y - 1));
            break;
        default:
            throw std::invalid_argument("Invalid piece.");
            break;
        }
        std::vector<std::pair<int, int>> valid_attacked_squares;
        std::copy_if(
            attacked_squares.begin(),
            attacked_squares.end(),
            std::back_inserter(valid_attacked_squares),
            [this](std::pair<int, int> square) { 
                return _is_valid_coordinate(square.first, square.second);
            }
        );
        return valid_attacked_squares;
    }

    bool ChessPiece::_is_valid_coordinate(int x, int y) {
        if (x < 0 || x > 7 || y < 0 || y > 7) {
            return false;
        }
        return true;
    }

    std::vector<ChessMove> ChessPiece::compute_possible_moves() {
        std::vector<ChessMove> legal_moves;
        std::vector<std::pair<int, int>> attacked_squares = compute_attacked_squares();

        switch (_piece)
        {
        case 'p':
        case 'P':
            int delta_row = _piece == 'p' ? 1 : -1;
            char queen_char = _piece == 'p' ? 'q' : 'Q';
            char rook_char = _piece == 'p' ? 'r' : 'R';
            char bishop_char = _piece == 'p' ? 'b' : 'B';
            char knight_char = _piece == 'p' ? 'n' : 'N';
            if (_x == 6) {
                legal_moves.push_back(ChessMove(_x, _y, _x + delta_row, _y, *_chess_board, true, queen_char));
                legal_moves.push_back(ChessMove(_x, _y, _x + delta_row, _y, *_chess_board, true, rook_char));
                legal_moves.push_back(ChessMove(_x, _y, _x + delta_row, _y, *_chess_board, true, bishop_char));
                legal_moves.push_back(ChessMove(_x, _y, _x + delta_row, _y, *_chess_board, true, knight_char));
                if (_belong_to_different_players(_chess_board->piece_at(_x + delta_row, _y + 1), _piece)) {
                    legal_moves.push_back(ChessMove(_x, _y, _x + delta_row, _y + 1, *_chess_board));
                }
                if (_belong_to_different_players(_chess_board->piece_at(_x + delta_row, _y - 1), _piece)) {
                    legal_moves.push_back(ChessMove(_x, _y, _x + delta_row, _y - 1, *_chess_board));
                }
            }
            else {
                if (_chess_board->piece_at(_x + delta_row, _y) == ' ') {
                    legal_moves.push_back(ChessMove(_x, _y, _x + delta_row, _y, *_chess_board));
                    if (_x == 1 && _chess_board->piece_at(_x + 2*delta_row, _y) == ' ') {
                        legal_moves.push_back(ChessMove(_x, _y, _x + 2*delta_row, _y, *_chess_board, false, ' ', true));
                    }
                }
                if (_belong_to_different_players(_chess_board->piece_at(_x + delta_row, _y + 1), _piece)) {
                    legal_moves.push_back(ChessMove(_x, _y, _x + delta_row, _y + 1, *_chess_board));
                }
                if (_belong_to_different_players(_chess_board->piece_at(_x + delta_row, _y - 1), _piece)) {
                    legal_moves.push_back(ChessMove(_x, _y, _x + delta_row, _y - 1, *_chess_board));
                }
            }
            // TODO: en passant
            break;
        case 'k':
        case 'K':
            /* code */
            break;
        default:
            for (std::pair<int, int> square : attacked_squares) {
                legal_moves.push_back(ChessMove(_x, _y, square.first, square.second, *_chess_board));
            }
            break;
        }

        for (std::pair<int, int> square : attacked_squares) {
            if (_chess_board->piece_at(square.first, square.second) == ' ') {
                legal_moves.push_back(ChessMove(_x, _y, square.first, square.second, *_chess_board));
            } else if (!_belong_to_same_player(_chess_board->piece_at(square.first, square.second), _piece)) {
                legal_moves.push_back(ChessMove(_x, _y, square.first, square.second, *_chess_board));
            }
        }
        return legal_moves;
    }

}

