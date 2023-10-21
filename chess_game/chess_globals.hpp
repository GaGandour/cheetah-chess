#ifndef _CHESS_GLOBALS_HPP_
#define _CHESS_GLOBALS_HPP_

#define WKING 'K'
#define WQUEEN 'Q'
#define WROOK 'R'
#define WBISHOP 'B'
#define WKNIGHT 'N'
#define WPAWN 'P'

#define BKING 'k'
#define BQUEEN 'q'
#define BROOK 'r'
#define BBISHOP 'b'
#define BKNIGHT 'n'
#define BPAWN 'p'

#define EMPTY ' '

#define WROW 7
#define BROW 0

#define WPAWN_ROW 6
#define BPAWN_ROW 1

#define LEFT_ROOK_COL 0
#define LEFT_KNIGHT_COL 1
#define LEFT_BISHOP_COL 2
#define QUEEN_COL 3
#define KING_COL 4
#define RIGHT_BISHOP_COL 5
#define RIGHT_KNIGHT_COL 6
#define RIGHT_ROOK_COL 7

#define KING_AFTER_BIG_CASTLE_COL 2
#define KING_AFTER_SMALL_CASTLE_COL 6

#define ROOK_AFTER_BIG_CASTLE_COL 3
#define ROOK_AFTER_SMALL_CASTLE_COL 5

#include <utility>
#include <vector>

static const std::pair<int, int> WKING_SQUARE = std::make_pair(WROW, KING_COL);
static const std::pair<int, int> BKING_SQUARE = std::make_pair(BROW, KING_COL);

static const std::pair<int, int> WKING_SQUARE_AFTER_BIG_CASTLE = std::make_pair(WROW, KING_AFTER_BIG_CASTLE_COL);
static const std::pair<int, int> BKING_SQUARE_AFTER_BIG_CASTLE = std::make_pair(BROW, KING_AFTER_BIG_CASTLE_COL);

static const std::pair<int, int> WKING_SQUARE_AFTER_SMALL_CASTLE = std::make_pair(WROW, KING_AFTER_SMALL_CASTLE_COL);
static const std::pair<int, int> BKING_SQUARE_AFTER_SMALL_CASTLE = std::make_pair(BROW, KING_AFTER_SMALL_CASTLE_COL);


static const std::pair<int, int> LEFT_WROOK_SQUARE = std::make_pair(7, 0);
static const std::pair<int, int> LEFT_BROOK_SQUARE = std::make_pair(0, 0);

static const std::pair<int, int> LEFT_WROOK_SQUARE_AFTER_CASTLE = std::make_pair(7, 3);
static const std::pair<int, int> LEFT_BROOK_SQUARE_AFTER_CASTLE = std::make_pair(0, 3);


static const std::pair<int, int> RIGHT_WROOK_SQUARE = std::make_pair(7, 7);
static const std::pair<int, int> RIGHT_BROOK_SQUARE = std::make_pair(0, 7);

static const std::pair<int, int> RIGHT_WROOK_SQUARE_AFTER_CASTLE = std::make_pair(7, 5);
static const std::pair<int, int> RIGHT_BROOK_SQUARE_AFTER_CASTLE = std::make_pair(0, 5);

static const std::vector<std::pair<int, int>> WBIG_CASTLE_INNER_SQUARES = {std::make_pair(WROW, 1), std::make_pair(WROW, 2), std::make_pair(WROW, 3)};
static const std::vector<std::pair<int, int>> WSMALL_CASTLE_INNER_SQUARES = {std::make_pair(WROW, 5), std::make_pair(WROW, 6)};

static const std::vector<std::pair<int, int>> BBIG_CASTLE_INNER_SQUARES = {std::make_pair(BROW, 1), std::make_pair(BROW, 2), std::make_pair(BROW, 3)};
static const std::vector<std::pair<int, int>> BSMALL_CASTLE_INNER_SQUARES = {std::make_pair(BROW, 5), std::make_pair(BROW, 6)};

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

#endif