#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include "./chess_fundamentals.hpp"

#define BOARD_SIZE 8

const char BOARD_SIZE_PLUS_ONE = BOARD_SIZE + 1;
const char BOARD_SIZE_MINUS_ONE = BOARD_SIZE - 1;

const PieceIndex WHITE = 0;
const PieceIndex BLACK = 1;

const PieceIndex PAWN = 2;
const PieceIndex KNIGHT = 4;
const PieceIndex BISHOP = 6;
const PieceIndex ROOK = 8;
const PieceIndex QUEEN = 10;
const PieceIndex KING = 12;

const BitBoard EMPTY_BITBOARD = hexadecimal_to_bitboard(0x0000000000000000);
const BitBoard UNIVERSE_BITBOARD = hexadecimal_to_bitboard(0xFFFFFFFFFFFFFFFF);

const BitBoard FILE_A = hexadecimal_to_bitboard(0x0101010101010101);
const BitBoard FILE_B = hexadecimal_to_bitboard(0x0202020202020202);
const BitBoard FILE_C = hexadecimal_to_bitboard(0x0404040404040404);
const BitBoard FILE_D = hexadecimal_to_bitboard(0x0808080808080808);
const BitBoard FILE_E = hexadecimal_to_bitboard(0x1010101010101010);
const BitBoard FILE_F = hexadecimal_to_bitboard(0x2020202020202020);
const BitBoard FILE_G = hexadecimal_to_bitboard(0x4040404040404040);
const BitBoard FILE_H = hexadecimal_to_bitboard(0x8080808080808080);

const BitBoard RANK_1 = hexadecimal_to_bitboard(0x00000000000000FF);
const BitBoard RANK_2 = hexadecimal_to_bitboard(0x000000000000FF00);
const BitBoard RANK_3 = hexadecimal_to_bitboard(0x0000000000FF0000);
const BitBoard RANK_4 = hexadecimal_to_bitboard(0x00000000FF000000);
const BitBoard RANK_5 = hexadecimal_to_bitboard(0x000000FF00000000);
const BitBoard RANK_6 = hexadecimal_to_bitboard(0x0000FF0000000000);
const BitBoard RANK_7 = hexadecimal_to_bitboard(0x00FF000000000000);
const BitBoard RANK_8 = hexadecimal_to_bitboard(0xFF00000000000000);

const BitBoard NOT_FILE_A = hexadecimal_to_bitboard(0xFEFEFEFEFEFEFEFE);
const BitBoard NOT_FILE_B = hexadecimal_to_bitboard(0xFDFDFDFDFDFDFDFD);
const BitBoard NOT_FILE_C = hexadecimal_to_bitboard(0xFBFBFBFBFBFBFBFB);
const BitBoard NOT_FILE_D = hexadecimal_to_bitboard(0xF7F7F7F7F7F7F7F7);
const BitBoard NOT_FILE_E = hexadecimal_to_bitboard(0xEFEFEFEFEFEFEFEF);
const BitBoard NOT_FILE_F = hexadecimal_to_bitboard(0xDFDFDFDFDFDFDFDF);
const BitBoard NOT_FILE_G = hexadecimal_to_bitboard(0xBFBFBFBFBFBFBFBF);
const BitBoard NOT_FILE_H = hexadecimal_to_bitboard(0x7F7F7F7F7F7F7F7F);

const BitBoard NOT_RANK_1 = hexadecimal_to_bitboard(0xFFFFFFFFFFFFFF00);
const BitBoard NOT_RANK_2 = hexadecimal_to_bitboard(0xFFFFFFFFFFFF00FF);
const BitBoard NOT_RANK_3 = hexadecimal_to_bitboard(0xFFFFFFFFFF00FFFF);
const BitBoard NOT_RANK_4 = hexadecimal_to_bitboard(0xFFFFFFFF00FFFFFF);
const BitBoard NOT_RANK_5 = hexadecimal_to_bitboard(0xFFFFFF00FFFFFFFF);
const BitBoard NOT_RANK_6 = hexadecimal_to_bitboard(0xFFFF00FFFFFFFFFF);
const BitBoard NOT_RANK_7 = hexadecimal_to_bitboard(0xFF00FFFFFFFFFFFF);
const BitBoard NOT_RANK_8 = hexadecimal_to_bitboard(0x00FFFFFFFFFFFFFF);

const BitBoard DIAGONAL_A1_H8 = hexadecimal_to_bitboard(0x8040201008040201);
const BitBoard DIAGONAL_H1_A8 = hexadecimal_to_bitboard(0x0102040810204080);

const BitBoard DARK_SQUARES = hexadecimal_to_bitboard(0xAA55AA55AA55AA55);
const BitBoard LIGHT_SQUARES = hexadecimal_to_bitboard(0x55AA55AA55AA55AA);

// clang-format off
enum EnumSquare {
  A1, A2, A3, A4, A5, A6, A7, A8,
  B1, B2, B3, B4, B5, B6, B7, B8,
  C1, C2, C3, C4, C5, C6, C7, C8,
  D1, D2, D3, D4, D5, D6, D7, D8,
  E1, E2, E3, E4, E5, E6, E7, E8,
  F1, F2, F3, F4, F5, F6, F7, F8,
  G1, G2, G3, G4, G5, G6, G7, G8,
  H1, H2, H3, H4, H5, H6, H7, H8
};

// clang-format on

#endif
