#ifndef _CHESS_MOVE_HPP_
#define _CHESS_MOVE_HPP_

#include <utility>


class ChessMove {
    public:
        /**
         * Constructor for ChessMove.
         */
        explicit ChessMove(
            int old_x, 
            int old_y, 
            int new_x, 
            int new_y,
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

        /**
         * Gets whether the move is a promotion.
         */
        bool is_promotion();

        /**
         * Gets the piece that the pawn is promoted to.
         */
        char get_promotion_piece();

        /**
         * Gets whether the move enables en passant.
         */
        bool enables_en_passant();

        /**
         * Gets the hash of the move.
         */
        long long get_move_hash();

    private:
        int _old_x;
        int _old_y;
        int _new_x;
        int _new_y;
        bool _is_capture;
        bool _is_promotion;
        char _promotion_piece;
        bool _enables_en_passant;
        long long _move_hash;
};


#endif