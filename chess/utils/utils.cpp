#include "./utils.hpp"
#include "./constants.hpp"
#include "chess_fundamentals.hpp"

BitBoard north_one_square(BitBoard bitboard) {
    return bitboard << BOARD_SIZE;
}

BitBoard south_one_square(BitBoard bitboard) {
    return bitboard >> BOARD_SIZE;
}

BitBoard east_one_square(BitBoard bitboard) {
    return (bitboard & NOT_FILE_H) << 1;
}

BitBoard west_one_square(BitBoard bitboard) {
    return (bitboard & NOT_FILE_A) >> 1;
}

BitBoard north_east_one_square(BitBoard bitboard) {
    return (bitboard & NOT_FILE_H) << BOARD_SIZE_PLUS_ONE;
}

BitBoard north_west_one_square(BitBoard bitboard) {
    return (bitboard & NOT_FILE_A) << BOARD_SIZE_MINUS_ONE;
}

BitBoard south_east_one_square(BitBoard bitboard) {
    return (bitboard & NOT_FILE_H) >> BOARD_SIZE_MINUS_ONE;
}

BitBoard south_west_one_square(BitBoard bitboard) {
    return (bitboard & NOT_FILE_A) >> BOARD_SIZE_PLUS_ONE;
}

BitBoard rotate_clockwise(BitBoard bitboard) {
    BitBoard result = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        BitBoard rank = (bitboard & RANK_1 << i * BOARD_SIZE);
        result |= rank >> i;
    }
    return result;
}
