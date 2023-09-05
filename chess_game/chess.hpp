#ifndef _CHESS_BOARD_HPP_
#define _CHESS_BOARD_HPP_

#include <utility>
#include <vector>
#include <stack>


namespace Chess {
    class ChessMove;
    class ChessBoard;
    class ChessGame;
    class ChessPiece;

    const static char INITIAL_CHESS_BOARD[8][8] = {
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
    };

    class ChessPiece {
        public:
            ChessPiece(int x, int y, ChessBoard *chess_board);
            std::vector<ChessMove> compute_possible_moves();
            std::vector<std::pair<int, int>> compute_attacked_squares();

        private:
            bool belong_to_same_player_(char piece1, char piece2);
            bool belong_to_different_players_(char piece1, char piece2);
            bool is_valid_coordinate_(int x, int y);
            void compute_rook_attacked_squares_(std::vector<std::pair<int,int>> &attacked_squares);
            void compute_knight_attacked_squares_(std::vector<std::pair<int,int>> &attacked_squares);
            void compute_queen_attacked_squares_(std::vector<std::pair<int,int>> &attacked_squares);
            void compute_bishop_attacked_squares_(std::vector<std::pair<int,int>> &attacked_squares);
            void compute_king_attacked_squares_(std::vector<std::pair<int,int>> &attacked_squares);
            char _piece;
            int _x;
            int _y;
            ChessBoard *_chess_board;
    };

    class ChessMove {
        public:
            /**
             * Constructor for ChessMove.
             */
            ChessMove(
                int old_x, 
                int old_y, 
                int new_x, 
                int new_y, 
                ChessBoard chess_board, 
                bool is_promotion = false, 
                char promotion_piece = ' ', 
                bool enables_en_passant = false
            );

            /**
             * Gets coordinates of the piece's position before the move.
             */
            std::pair<int, int> get_old_position();
            
            /**
             *  Gets coordinates of the piece's position after the move. 
             */
            std::pair<int, int> get_new_position();

            /**
             * Gets whether the move is a capture.
             */
            bool is_capture();

        private:
            int _old_x;
            int _old_y;
            int _new_x;
            int _new_y;
            bool _is_capture;
            bool _is_promotion;
            char _promotion_piece;
            bool _enables_en_passant;
    };
    
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
}

#endif