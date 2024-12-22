#ifndef UTILS_HPP
#define UTILS_HPP

#include "./chess_fundamentals.hpp"

BitBoard north_one_square(BitBoard bitboard);
BitBoard south_one_square(BitBoard bitboard);
BitBoard east_one_square(BitBoard bitboard);
BitBoard west_one_square(BitBoard bitboard);
BitBoard north_east_one_square(BitBoard bitboard);
BitBoard north_west_one_square(BitBoard bitboard);
BitBoard south_east_one_square(BitBoard bitboard);
BitBoard south_west_one_square(BitBoard bitboard);

BitBoard rotate_clockwise(BitBoard bitboard);
BitBoard rotate_counterclockwise(BitBoard bitboard);

#endif
