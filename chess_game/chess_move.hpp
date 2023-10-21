#ifndef _CHESS_MOVE_HPP_
#define _CHESS_MOVE_HPP_

#include <utility>

enum MoveType {
    NORMAL,
    NORMAL_CAPTURE,
    EN_PASSANT,
    SMALL_CASTLE,
    BIG_CASTLE
};


typedef struct ChessMoveParams {
    int old_x;
    int old_y;
    int new_x;
    int new_y;
    bool is_white_moving;

    MoveType move_type = MoveType::NORMAL;

    bool is_promotion = false;
    char promotion_piece = ' ';
    
    char moving_piece = ' ';
    char captured_piece = ' ';
    
    bool enables_en_passant = false;
} ChessMoveParams;


class ChessMove {
    public:
        /**
         * Constructor for ChessMove.
         */
        explicit ChessMove(
            ChessMoveParams params
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
         * Gets the type of the move.
         */
        MoveType get_move_type();

        /**
         * Gets whether the move is a capture.
         */
        bool is_capture();


        /**
         * Gets the piece that is moving.
         */
        char get_moving_piece();

        /**
         * Gets the piece that is captured.
         */
        char get_captured_piece();

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
         * Gets whether the move is a castle.
        */
        bool is_castle();

        /**
         * Gets the hash of the move.
         */
        long long get_move_hash();

    private:
        int _old_x;
        int _old_y;
        int _new_x;
        int _new_y;

        MoveType _move_type;
        
        bool _is_promotion;
        char _promotion_piece;
        
        char _moving_piece;
        char _captured_piece;

        bool _enables_en_passant;
        long long _move_hash;
};


#endif