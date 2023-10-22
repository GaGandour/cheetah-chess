#include "chess_game.hpp"
#include "chess_board.hpp"
#include "chess_move.hpp"
#include "chess_piece.hpp"

#include <stack>
#include <utility>
#include <vector>
#include <iostream>

// Implementation of ChessGame methods.

ChessGame::ChessGame() {
    while (!_chess_board_stack.empty()) {
        _chess_board_stack.pop();
    }
    _current_board = new ChessBoard();
    _chess_board_stack.push(_current_board);
    _result = GameResult::IN_PROGRESS;
}

ChessGame::ChessGame(ChessBoard *chess_board) {
    while (!_chess_board_stack.empty()) {
        _chess_board_stack.pop();
    }
    _current_board = chess_board;
    _chess_board_stack.push(_current_board);
    // TODO: Compute result.
}

void ChessGame::make_move(ChessMove *chess_move) {
    _current_board = new ChessBoard(_current_board, chess_move);
    _chess_board_stack.push(_current_board);
    // TODO: Compute game result.
}

void ChessGame::undo_move() {
    _chess_board_stack.pop();
    _current_board = _chess_board_stack.top();
    _result = GameResult::IN_PROGRESS;
}

void ChessGame::print_board() {
    _current_board->print_board();
}

bool ChessGame::has_game_ended() {
    return _result != GameResult::IN_PROGRESS;
}

GameResult ChessGame::result() {
    return _result;
}

bool ChessGame::is_white_turn() {
    return _current_board->is_white_turn();
}

long long ChessGame::get_board_hash() {
    return _current_board->get_board_hash();
}


