#ifndef PIECE_HPP
#define PIECE_HPP

#include <vector>

#include "../game_state_information/game_state_information.hpp"
#include "../move/move.hpp"
#include "../square/square.hpp"
#include "../utils/utils.hpp"

class Piece {
    /*
     * A piece is a single piece on the board. It has a color and a type.
     * */
   protected:
    Color color;

   public:
    Piece(Color color) : color(color) {}

    Color getColor() const { return color; }

    virtual std::vector<ChessMove> simple_valid_moves(
        Piece board[BOARD_SIZE][BOARD_SIZE], const Square origin, const GameStateInformation game_state_information
    ) = 0;
};

class Pawn : public Piece {
    /*
     * A pawn is a piece that can move forward and capture diagonally.
     * */
   public:
    Pawn(Color color) : Piece(color) {}
};

class Knight : public Piece {
    /*
     * A knight is a piece that can move in an L shape.
     * */
   public:
    Knight(Color color) : Piece(color) {}
};

class Bishop : public Piece {
    /*
     * A bishop is a piece that can move diagonally.
     * */
   public:
    Bishop(Color color) : Piece(color) {}
};

class Rook : public Piece {
    /*
     * A rook is a piece that can move horizontally and vertically.
     * */
   public:
    Rook(Color color) : Piece(color) {}
};

class Queen : public Piece {
    /*
     * A queen is a piece that can move horizontally, vertically and diagonally.
     * */
   public:
    Queen(Color color) : Piece(color) {}
};

class King : public Piece {
    /*
     * A king is a piece that can move in any direction, but only one square at a time.
     * */
   public:
    King(Color color) : Piece(color) {}
};

#endif
