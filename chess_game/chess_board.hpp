#ifndef _CHESS_BOARD_HPP_
#define _CHESS_BOARD_HPP_

#include <utility>
#include <unordered_map>

#include "chess_move.hpp"
#include "chess_globals.hpp"


class ChessBoard {
    public:
        ChessBoard();
        ChessBoard(ChessBoard *previous_board, ChessMove *chess_move);
        long long get_board_hash();
        void print_board();
        bool is_white_turn();
        bool is_black_turn();
        
        char piece_at(int x, int y);
        char piece_at(std::pair<int, int> &position);

        bool is_occupied(int x, int y);
        bool is_occupied(std::pair<int, int> &position);
        
        int get_num_moves();
        int get_num_moves_since_last_capture();

        bool can_white_big_castle();
        bool can_white_small_castle();
        bool can_black_big_castle();
        bool can_black_small_castle();

        bool is_en_passant_enabled();
        std::pair<int, int> get_en_passant_square();

    private:
        void _reset_board();

        void _set_piece_at(int x, int y, char piece);
        void _set_piece_at(std::pair<int, int> &position, char piece);

        /**
         * If the move involves a king or a rook, revoke the relevant castle rights.
         */
        void _check_for_castle_rights(std::pair<int, int> &old_position);
        
        bool _white_turn;
        char _chess_board[8][8];

        std::unordered_map<char, int> _num_pieces;

        bool _can_white_big_castle;
        bool _can_white_small_castle;
        bool _can_black_big_castle;
        bool _can_black_small_castle;

        int _num_moves;
        int _num_moves_since_last_capture;

        bool _en_passant_enabled;
        std::pair<int, int> _en_passant_square;
        
        long long _board_hash;
};

bool is_valid_coordinate(int x, int y) {
    if (x > 7 || x < 0 || y > 7 || y < 0)
        return false;
    return true;
}

#endif