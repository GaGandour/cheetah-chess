#ifndef _CHESS_PIECE_HPP_
#define _CHESS_PIECE_HPP_

#include <utility>
#include <vector>
#include <stack>

// is upper, lower
#include <cstring>
#include <cctype>

#include "chess_board.hpp"
#include "chess_move.hpp"

bool piece_is_white(char piece) {
    return (bool)isupper(piece);
}

bool piece_is_black(char piece) {
    return (bool)islower(piece);
}

bool belong_to_different_players(char piece1, char piece2) {
    if (piece1 == ' ' || piece2 == ' ') {
        return false;
    }
    bool piece1_is_white = piece_is_white(piece1);
    bool piece2_is_white = piece_is_white(piece2);
    return (piece1_is_white ^ piece2_is_white);
}

bool belong_to_same_player(char piece1, char piece2) {
    if (piece1 == ' ' || piece2 == ' ') {
        return false;
    }
    bool piece1_is_white = piece_is_white(piece1);
    bool piece2_is_white = piece_is_white(piece2);
    return !(piece1_is_white ^ piece2_is_white);
}

class ChessPiece {
    public:
        ChessPiece() {};
        virtual ~ChessPiece() {};
        virtual void compute_attacked_squares(std::pair<int, int> &position, ChessBoard *chess_board, std::vector<std::pair<int, int>> &attacked_squares) = 0;
        virtual std::vector<ChessMove> compute_possible_moves_disregarding_check(std::pair<int, int> &position, ChessBoard *chess_board);
        
        bool is_white() {
            return _is_white;
        }

    protected:
        bool _is_white;
        char _piece_code;
};

class King : public ChessPiece {
    public:
        virtual void compute_attacked_squares(std::pair<int, int> &position, ChessBoard *chess_board, std::vector<std::pair<int, int>> &attacked_squares);
        virtual std::vector<ChessMove> compute_possible_moves_disregarding_check(std::pair<int, int> &position, ChessBoard *chess_board);
    protected:
        virtual void _compute_and_push_castle_moves(std::pair<int, int> &position, ChessBoard *chess_board, std::vector<ChessMove> moves);
        virtual void _validate_and_push_castle_move(ChessBoard *chess_board, std::vector<ChessMove> moves, bool is_big_castle);
};

class Queen : public ChessPiece {
    public:
        virtual void compute_attacked_squares(std::pair<int, int> &position, ChessBoard *chess_board, std::vector<std::pair<int, int>> &attacked_squares);
};

class Bishop : public ChessPiece {
    public:
        virtual void compute_attacked_squares(std::pair<int, int> &position, ChessBoard *chess_board, std::vector<std::pair<int, int>> &attacked_squares);
};

class Knight : public ChessPiece {
    public:
        virtual void compute_attacked_squares(std::pair<int, int> &position, ChessBoard *chess_board, std::vector<std::pair<int, int>> &attacked_squares);
};

class Rook : public ChessPiece {
    public:
        virtual void compute_attacked_squares(std::pair<int, int> &position, ChessBoard *chess_board, std::vector<std::pair<int, int>> &attacked_squares);
};

class Pawn : public ChessPiece {
    public:
        virtual void compute_attacked_squares(std::pair<int, int> &position, ChessBoard *chess_board, std::vector<std::pair<int, int>> &attacked_squares);
        virtual std::vector<ChessMove> compute_possible_moves_disregarding_check(std::pair<int, int> &position, ChessBoard *chess_board);
};

class WKing : public King {
    public:
        WKing() {
            _is_white = true;
            _piece_code = WKING;
        };
};

class WQueen : public Queen {
    public:
        WQueen() {
            _is_white = true;
            _piece_code = WQUEEN;
        };
};

class WBishop : public Bishop {
    public:
        WBishop() {
            _is_white = true;
            _piece_code = WBISHOP;
        };
};

class WKnight : public Knight {
    public:
        WKnight() {
            _is_white = true;
            _piece_code = WKNIGHT;
        };
};

class WRook : public Rook {
    public:
        WRook() {
            _is_white = true;
            _piece_code = WROOK;
        };
};

class WPawn : public Pawn {
    public:
        WPawn() {
            _is_white = true;
            _piece_code = WPAWN;
        };
};


class BKing : public King {
    public:
        BKing() {
            _is_white = false;
            _piece_code = BKING;
        };
};

class BQueen : public Queen {
    public:
        BQueen() {
            _is_white = false;
            _piece_code = BQUEEN;
        };
};

class BBishop : public Bishop {
    public:
        BBishop() {
            _is_white = false;
            _piece_code = BBISHOP;
        };
};

class BKnight : public Knight {
    public:
        BKnight() {
            _is_white = false;
            _piece_code = BKNIGHT;
        };
};

class BRook : public Rook {
    public:
        BRook() {
            _is_white = false;
            _piece_code = BROOK;
        };
};

class BPawn : public Pawn {
    public:
        BPawn() {
            _is_white = false;
            _piece_code = BPAWN;
        };
};



ChessPiece *generate_piece_from_code(char piece_code) {
    switch (piece_code)
    {
    case BKING:
        return new BKing();
    case WKING:
        return new WKing();
    case BQUEEN:
        return new BQueen();
    case WQUEEN:
        return new WQueen();
    case BBISHOP:
        return new BBishop();
    case WBISHOP:
        return new WBishop();
    case BKNIGHT:
        return new BKnight();
    case WKNIGHT:
        return new WKnight();
    case BROOK:
        return new BRook();
    case WROOK:
        return new WRook();
    default:
        return NULL;
    }
}


#endif