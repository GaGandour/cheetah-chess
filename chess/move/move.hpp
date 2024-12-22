#ifndef CHESS_MOVE_HPP
#define CHESS_MOVE_HPP

class ChessMove {
    /*
     * This class represents a move in a chess game.
     * */
  private:
    int origin_line;
    int origin_column;
    int destination_line;
    int destination_column;

    bool is_capture;
    bool is_castle;

  public:
    ChessMove(int origin_line, int origin_column, int destination_line, int destination_column, bool is_capture,
              bool is_castle);

    int getOriginLine() const;
    int getOriginColumn() const;

    int getDestinationLine() const;
    int getDestinationColumn() const;

    bool isCapture() const;
    bool isCastle() const;
};

#endif
