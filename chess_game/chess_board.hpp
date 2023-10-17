#ifndef _CHESS_BOARD_HPP_
#define _CHESS_BOARD_HPP_

#include <utility>

#include "chess_move.hpp"


static const char INITIAL_CHESS_BOARD[8][8] = {
    {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
    {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
};

static const std::pair<int, int> WKING_SQUARE = std::make_pair(7, 4);
static const std::pair<int, int> BKING_SQUARE = std::make_pair(0, 4);

static const std::pair<int, int> LEFT_WROOK_SQUARE = std::make_pair(7, 0);
static const std::pair<int, int> LEFT_BROOK_SQUARE = std::make_pair(0, 0);

static const std::pair<int, int> RIGHT_WROOK_SQUARE = std::make_pair(7, 7);
static const std::pair<int, int> RIGHT_BROOK_SQUARE = std::make_pair(0, 7);

class ChessBoard {
    public:
        ChessBoard();
        ChessBoard(ChessBoard *previous_board, ChessMove *chess_move);
        long long get_board_hash();
        void print_board();
        bool is_white_turn();
        char piece_at(int x, int y);
        bool is_occupied(int x, int y);
        
        int get_num_moves();
        int get_num_moves_since_last_capture();

        
    private:
        void _reset_board();
        void _check_for_castle_rights(std::pair<int, int> &old_position);
        
        bool _white_turn;
        char _chess_board[8][8];

        bool _can_white_big_castle;
        bool _can_white_small_castle;
        bool _can_black_big_castle;
        bool _can_black_small_castle;

        int _num_moves;
        int _num_moves_since_last_capture;
        
        long long _board_hash;
};

bool is_valid_coordinate(int x, int y) {
    if (x > 7 || x < 0 || y > 7 || y < 0)
        return false;
    return true;
}

#endif