#ifndef _CHESS_PIECE_HPP_
#define _CHESS_PIECE_HPP_

#include <utility>
#include <vector>
#include <stack>

// is upper
#include <cstring>
#include <cctype>

#include "chess_board.hpp"
#include "chess_move.hpp"


class ChessPiece {
    public:
        ChessPiece() {};
        virtual ~ChessPiece() {};
        virtual void compute_attacked_squares(std::pair<int, int> &position, ChessBoard *chess_board, std::vector<std::pair<int, int>> attacked_squares) = 0;
        virtual std::vector<ChessMove> compute_possible_moves_disregarding_check(std::pair<int, int> &position, ChessBoard *chess_board);

    protected:
        bool is_white;
        char piece_code;
};

class King : public ChessPiece {
    public:
        virtual void compute_attacked_squares(std::pair<int, int> &position, ChessBoard *chess_board, std::vector<std::pair<int, int>> attacked_squares);
        virtual std::vector<ChessMove> compute_possible_moves_disregarding_check(std::pair<int, int> &position, ChessBoard *chess_board);
};

class Queen : public ChessPiece {
    public:
        virtual void compute_attacked_squares(std::pair<int, int> &position, ChessBoard *chess_board, std::vector<std::pair<int, int>> attacked_squares);
};

class Bishop : public ChessPiece {
    public:
        virtual void compute_attacked_squares(std::pair<int, int> &position, ChessBoard *chess_board, std::vector<std::pair<int, int>> attacked_squares);
};

class Knight : public ChessPiece {
    public:
        virtual void compute_attacked_squares(std::pair<int, int> &position, ChessBoard *chess_board, std::vector<std::pair<int, int>> attacked_squares);
};

class Rook : public ChessPiece {
    public:
        virtual void compute_attacked_squares(std::pair<int, int> &position, ChessBoard *chess_board, std::vector<std::pair<int, int>> attacked_squares);
};

class Pawn : public ChessPiece {
    public:
        virtual void compute_attacked_squares(std::pair<int, int> &position, ChessBoard *chess_board, std::vector<std::pair<int, int>> attacked_squares);
        virtual std::vector<ChessMove> compute_possible_moves_disregarding_check(std::pair<int, int> &position, ChessBoard *chess_board);
};

class WKing : public King {
    public:
        WKing() {
            is_white = true;
            piece_code = 'K';
        };
};

class WQueen : public Queen {
    public:
        WQueen() {
            is_white = true;
            piece_code = 'Q';
        };
};

class WBishop : public Bishop {
    public:
        WBishop() {
            is_white = true;
            piece_code = 'B';
        };
};

class WKnight : public Knight {
    public:
        WKnight() {
            is_white = true;
            piece_code = 'N';
        };
};

class WRook : public Rook {
    public:
        WRook() {
            is_white = true;
            piece_code = 'R';
        };
};

class WPawn : public Pawn {
    public:
        WPawn() {
            is_white = true;
            piece_code = 'P';
        };
};


class BKing : public King {
    public:
        BKing() {
            is_white = false;
            piece_code = 'k';
        };
};

class BQueen : public Queen {
    public:
        BQueen() {
            is_white = false;
            piece_code = 'q';
        };
};

class BBishop : public Bishop {
    public:
        BBishop() {
            is_white = false;
            piece_code = 'b';
        };
};

class BKnight : public Knight {
    public:
        BKnight() {
            is_white = false;
            piece_code = 'n';
        };
};

class BRook : public Rook {
    public:
        BRook() {
            is_white = false;
            piece_code = 'r';
        };
};

class BPawn : public Pawn {
    public:
        BPawn() {
            is_white = false;
            piece_code = 'p';
        };
};

bool belong_to_different_players(char piece1, char piece2) {
    if (piece1 == ' ' || piece2 == ' ') {
        return false;
    }
    bool piece1_is_white = (bool)isupper(piece1);
    bool piece2_is_white = (bool)isupper(piece2);
    return (piece1_is_white ^ piece2_is_white);
}

bool belong_to_same_player(char piece1, char piece2) {
    if (piece1 == ' ' || piece2 == ' ') {
        return false;
    }
    bool piece1_is_white = (bool)isupper(piece1);
    bool piece2_is_white = (bool)isupper(piece2);
    return !(piece1_is_white ^ piece2_is_white);
}

ChessPiece *generate_piece_from_code(char piece_code) {
    switch (piece_code)
    {
    case 'k':
        return new BKing();
    case 'K':
        return new WKing();
    case 'q':
        return new BQueen();
    case 'Q':
        return new WQueen();
    case 'b':
        return new BBishop();
    case 'B':
        return new WBishop();
    case 'n':
        return new BKnight();
    case 'N':
        return new WKnight();
    case 'r':
        return new BRook();
    case 'R':
        return new WRook();
    default:
        return NULL;
    }
}


#endif