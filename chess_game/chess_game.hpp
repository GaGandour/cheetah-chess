#ifndef _CHESS_GAME_HPP_
#define _CHESS_GAME_HPP_

#include <utility>
#include <vector>
#include <stack>

class ChessBoard {
    public:
        ChessBoard();
        ChessBoard(ChessBoard previous_board, ChessMove chess_move);
        long long get_board_hash();
        std::vector<ChessMove> compute_legal_moves();
        std::vector<ChessMove> compute_legal_moves(int x, int y);
        void print_board();
        bool is_white_turn();
        char piece_at(int x, int y);
        bool is_occupied(int x, int y);
        bool is_check();
        bool is_checkmate();
        bool is_stalemate();

        
    private:
        bool _can_white_big_castle;
        bool _can_white_small_castle;
        bool _can_black_big_castle;
        bool _can_black_small_castle;
        char _chess_board[8][8];
        bool _white_turn;
        int _num_moves;
        int _num_moves_since_capture;
        long long _board_hash;
        void _reset_board();
};

class ChessGame {
    public:
        ChessGame();
        std::vector<ChessMove> compute_legal_moves();
        std::vector<ChessMove> compute_legal_moves(int x, int y);
        void make_move(ChessMove chess_move);
        void undo_move();
        void print_board();
        bool has_game_ended();
        bool is_check();
        int result();
        bool is_white_turn();
        long long get_board_hash();
        
    private:
        std::stack<ChessBoard> _chess_board_stack;
        bool _white_turn;
};

#endif