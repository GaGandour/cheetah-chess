#ifndef _CHESS_GAME_HPP_
#define _CHESS_GAME_HPP_

#include <utility>
#include <vector>
#include <stack>

#include "chess_move.hpp"
#include "chess_board.hpp"
#include "chess_globals.hpp"
#include "chess_piece.hpp"

enum GameResult {
    WHITE_WIN,
    BLACK_WIN,
    DRAW,
    IN_PROGRESS
};

class ChessGame {
    public:
        ChessGame();
        ChessGame(ChessBoard *chess_board);
        
        std::vector<ChessMove> compute_legal_moves();
        std::vector<ChessMove> compute_legal_moves(int x, int y);
        
        void make_move(ChessMove *chess_move);
        void undo_move();
        
        void print_board();
        
        bool is_check();

        bool has_game_ended();
        GameResult result();
        
        bool is_white_turn();

        long long get_board_hash();
        
    private:
        std::stack<ChessBoard*> _chess_board_stack;
        ChessBoard *_current_board;
        GameResult _result;
};

#endif