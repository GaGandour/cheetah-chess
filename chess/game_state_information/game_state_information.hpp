#ifndef GAME_STATE_INFORMATION_HPP
#define GAME_STATE_INFORMATION_HPP

#include "../square/square.hpp"
#include <optional>

enum class Color { WHITE, BLACK };

class GameStateInformation {
  private:
    Color current_turn;
    bool white_short_castle_allowed;
    bool white_long_castle_allowed;
    bool black_short_castle_allowed;
    bool black_long_castle_allowed;

    std::optional<Square> en_passant_square;

  public:
    GameStateInformation(Color current_turn, bool white_short_castle_allowed, bool white_long_castle_allowed,
                         bool black_short_castle_allowed, bool black_long_castle_allowed)
        : current_turn(current_turn), white_short_castle_allowed(white_short_castle_allowed),
          white_long_castle_allowed(white_long_castle_allowed), black_short_castle_allowed(black_short_castle_allowed),
          black_long_castle_allowed(black_long_castle_allowed) {}

    GameStateInformation(Color current_turn, bool white_short_castle_allowed, bool white_long_castle_allowed,
                         bool black_short_castle_allowed, bool black_long_castle_allowed,
                         std::optional<Square> en_passant_square)
        : current_turn(current_turn), white_short_castle_allowed(white_short_castle_allowed),
          white_long_castle_allowed(white_long_castle_allowed), black_short_castle_allowed(black_short_castle_allowed),
          black_long_castle_allowed(black_long_castle_allowed), en_passant_square(en_passant_square) {}

    Color getCurrentTurn() const;
    bool isWhiteShortCastleAllowed() const;
    bool isWhiteLongCastleAllowed() const;
    bool isBlackShortCastleAllowed() const;
    bool isBlackLongCastleAllowed() const;
    bool isEnPassantAllowed() const;

    std::optional<Square> getEnPassantSquare() const;
};

#endif
