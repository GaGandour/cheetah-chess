#include "chess.hpp"

#include <utility>
// #include <vector>
#include <iostream>
#include <algorithm>

// Implementations of ChessPiece methods.
namespace Chess {
    ChessPiece::ChessPiece(int x, int y, ChessBoard *chess_board) {
        piece_ = chess_board->piece_at(x, y);
        x_ = x;
        y_ = y;
        chess_board_ = chess_board;
    }

    bool ChessPiece::belong_to_same_player_(char piece1, char piece2) {
        if (piece1 == ' ' || piece2 == ' ') {
            return false;
        }
        char difference = piece1 - piece2;
        if (difference < 26 && difference > -26) {
            return true;
        }
        return false;
    }

    bool ChessPiece::belong_to_different_players_(char piece1, char piece2) {
        if (piece1 == ' ' || piece2 == ' ') {
            return false;
        }
        char difference = piece1 - piece2;
        if (difference < 26 && difference > -26) {
            return false;
        }
        return true;
    }

    void ChessPiece::compute_rook_attacked_squares_(std::vector<std::pair<int,int>> &attacked_squares) {
        int i = 0;
        while (is_valid_coordinate_(x_ + i, y_) && !belong_to_same_player_(chess_board_->piece_at(x_ + i, y_), piece_)) {
            attacked_squares.push_back(std::make_pair(x_ + i, y_));
            i++;
            if (belong_to_same_player_(chess_board_->piece_at(x_ + i, y_), piece_)) {
                break;
            }
        }
        i = 0;
        while (is_valid_coordinate_(x_ - i, y_) && !belong_to_same_player_(chess_board_->piece_at(x_ - i, y_), piece_)) {
            attacked_squares.push_back(std::make_pair(x_ - i, y_));
            i++;
            if (belong_to_same_player_(chess_board_->piece_at(x_ - i, y_), piece_)) {
                break;
            }
        }
        i = 0;
        while (is_valid_coordinate_(x_, y_ + i) && !belong_to_same_player_(chess_board_->piece_at(x_, y_ + i), piece_)) {
            attacked_squares.push_back(std::make_pair(x_, y_ + i));
            i++;
            if (belong_to_same_player_(chess_board_->piece_at(x_, y_ + i), piece_)) {
                break;
            }
        }
        i = 0;
        while (is_valid_coordinate_(x_, y_ - i) && !belong_to_same_player_(chess_board_->piece_at(x_, y_ - i), piece_)) {
            attacked_squares.push_back(std::make_pair(x_, y_ - i));
            i++;
            if (belong_to_same_player_(chess_board_->piece_at(x_, y_ - i), piece_)) {
                break;
            }
        }
    }

    void ChessPiece::compute_knight_attacked_squares_(std::vector<std::pair<int,int>> &attacked_squares) {
        attacked_squares.push_back(std::make_pair(x_ + 2, y_ + 1));
        attacked_squares.push_back(std::make_pair(x_ + 2, y_ - 1));
        attacked_squares.push_back(std::make_pair(x_ - 2, y_ + 1));
        attacked_squares.push_back(std::make_pair(x_ - 2, y_ - 1));
        attacked_squares.push_back(std::make_pair(x_ + 1, y_ + 2));
        attacked_squares.push_back(std::make_pair(x_ + 1, y_ - 2));
        attacked_squares.push_back(std::make_pair(x_ - 1, y_ + 2));
        attacked_squares.push_back(std::make_pair(x_ - 1, y_ - 2));
    }

    void ChessPiece::compute_king_attacked_squares_(std::vector<std::pair<int,int>> &attacked_squares) {
        attacked_squares.push_back(std::make_pair(x_ + 1, y_));
        attacked_squares.push_back(std::make_pair(x_ - 1, y_));
        attacked_squares.push_back(std::make_pair(x_, y_ + 1));
        attacked_squares.push_back(std::make_pair(x_, y_ - 1));
        attacked_squares.push_back(std::make_pair(x_ + 1, y_ + 1));
        attacked_squares.push_back(std::make_pair(x_ + 1, y_ - 1));
        attacked_squares.push_back(std::make_pair(x_ - 1, y_ + 1));
        attacked_squares.push_back(std::make_pair(x_ - 1, y_ - 1));
    }

    void ChessPiece::compute_queen_attacked_squares_(std::vector<std::pair<int,int>> &attacked_squares) {
        compute_rook_attacked_squares_(attacked_squares);
        compute_bishop_attacked_squares_(attacked_squares);
    }

    void ChessPiece::compute_bishop_attacked_squares_(std::vector<std::pair<int,int>> &attacked_squares) {
        int i = 0;
        while (is_valid_coordinate_(x_ + i, y_ + i) && !belong_to_same_player_(chess_board_->piece_at(x_ + i, y_ + i), piece_)) {
            attacked_squares.push_back(std::make_pair(x_ + i, y_ + i));
            i++;
            if (belong_to_same_player_(chess_board_->piece_at(x_ + i, y_ + i), piece_)) {
                break;
            }
        }
        i = 0;
        while (is_valid_coordinate_(x_ - i, y_ + i) && !belong_to_same_player_(chess_board_->piece_at(x_ - i, y_ + i), piece_)) {
            attacked_squares.push_back(std::make_pair(x_ - i, y_ + i));
            i++;
            if (belong_to_same_player_(chess_board_->piece_at(x_ - i, y_ + i), piece_)) {
                break;
            }
        }
        i = 0;
        while (is_valid_coordinate_(x_ + i, y_ - i) && !belong_to_same_player_(chess_board_->piece_at(x_ + i, y_ - i), piece_)) {
            attacked_squares.push_back(std::make_pair(x_ + i, y_ - i));
            i++;
            if (belong_to_same_player_(chess_board_->piece_at(x_ + i, y_ - i), piece_)) {
                break;
            }
        }
        i = 0;
        while (is_valid_coordinate_(x_ - i, y_ - i) && !belong_to_same_player_(chess_board_->piece_at(x_ - i, y_ - i), piece_)) {
            attacked_squares.push_back(std::make_pair(x_ - i, y_ - i));
            i++;
            if (belong_to_same_player_(chess_board_->piece_at(x_ - i, y_ - i), piece_)) {
                break;
            }
        }
    }

    std::vector<std::pair<int, int>> ChessPiece::compute_attacked_squares() {
        std::vector<std::pair<int, int>> attacked_squares;
        switch (piece_)
        {
        case 'n':
        case 'N':
            compute_knight_attacked_squares_(attacked_squares);
            break;
        case 'r':
        case 'R':
            compute_rook_attacked_squares_(attacked_squares);
            break;
        case 'b':
        case 'B':
            compute_bishop_attacked_squares_(attacked_squares);
            break;
        case 'q':
        case 'Q':
            compute_queen_attacked_squares_(attacked_squares);
            break;
        case 'k':
        case 'K':
            compute_king_attacked_squares_(attacked_squares);
            break;
        case 'p':
            attacked_squares.push_back(std::make_pair(x_ + 1, y_ + 1));
            attacked_squares.push_back(std::make_pair(x_ + 1, y_ - 1));
            break;
        case 'P':
            attacked_squares.push_back(std::make_pair(x_ - 1, y_ + 1));
            attacked_squares.push_back(std::make_pair(x_ - 1, y_ - 1));
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
                return is_valid_coordinate_(square.first, square.second);
            }
        );
        return valid_attacked_squares;
    }

    bool ChessPiece::is_valid_coordinate_(int x, int y) {
        if (x < 0 || x > 7 || y < 0 || y > 7) {
            return false;
        }
        return true;
    }

    std::vector<ChessMove> ChessPiece::compute_possible_moves() {
        std::vector<ChessMove> legal_moves;
        std::vector<std::pair<int, int>> attacked_squares = compute_attacked_squares();

        switch (piece_)
        {
        case 'p':
        case 'P':
            int delta_row = piece_ == 'p' ? 1 : -1;
            char queen_char = piece_ == 'p' ? 'q' : 'Q';
            char rook_char = piece_ == 'p' ? 'r' : 'R';
            char bishop_char = piece_ == 'p' ? 'b' : 'B';
            char knight_char = piece_ == 'p' ? 'n' : 'N';
            if (x_ == 6) {
                legal_moves.push_back(ChessMove(x_, y_, x_ + delta_row, y_, *chess_board_, true, queen_char));
                legal_moves.push_back(ChessMove(x_, y_, x_ + delta_row, y_, *chess_board_, true, rook_char));
                legal_moves.push_back(ChessMove(x_, y_, x_ + delta_row, y_, *chess_board_, true, bishop_char));
                legal_moves.push_back(ChessMove(x_, y_, x_ + delta_row, y_, *chess_board_, true, knight_char));
                if (belong_to_different_players_(chess_board_->piece_at(x_ + delta_row, y_ + 1), piece_)) {
                    legal_moves.push_back(ChessMove(x_, y_, x_ + delta_row, y_ + 1, *chess_board_));
                }
                if (belong_to_different_players_(chess_board_->piece_at(x_ + delta_row, y_ - 1), piece_)) {
                    legal_moves.push_back(ChessMove(x_, y_, x_ + delta_row, y_ - 1, *chess_board_));
                }
            }
            else {
                if (chess_board_->piece_at(x_ + delta_row, y_) == ' ') {
                    legal_moves.push_back(ChessMove(x_, y_, x_ + delta_row, y_, *chess_board_));
                    if (x_ == 1 && chess_board_->piece_at(x_ + 2*delta_row, y_) == ' ') {
                        legal_moves.push_back(ChessMove(x_, y_, x_ + 2*delta_row, y_, *chess_board_, false, ' ', true));
                    }
                }
                if (belong_to_different_players_(chess_board_->piece_at(x_ + delta_row, y_ + 1), piece_)) {
                    legal_moves.push_back(ChessMove(x_, y_, x_ + delta_row, y_ + 1, *chess_board_));
                }
                if (belong_to_different_players_(chess_board_->piece_at(x_ + delta_row, y_ - 1), piece_)) {
                    legal_moves.push_back(ChessMove(x_, y_, x_ + delta_row, y_ - 1, *chess_board_));
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
                legal_moves.push_back(ChessMove(x_, y_, square.first, square.second, *chess_board_));
            }
            break;
        }

        for (std::pair<int, int> square : attacked_squares) {
            if (chess_board_->piece_at(square.first, square.second) == ' ') {
                legal_moves.push_back(ChessMove(x_, y_, square.first, square.second, *chess_board_));
            } else if (!belong_to_same_player_(chess_board_->piece_at(square.first, square.second), piece_)) {
                legal_moves.push_back(ChessMove(x_, y_, square.first, square.second, *chess_board_));
            }
        }
        return legal_moves;
    }

}

