#include "chess_game/chess.hpp"
#include <utility>
#include <iostream>

using namespace std;

int main() {
    Chess::ChessBoard chess_board = Chess::ChessBoard();
    Chess::ChessMove chess_move(0, 0, 1, 1, chess_board);
    pair<int, int> p = chess_move.get_old_position();
    cout << p.first << " " << p.second << endl;
    return 0;
}