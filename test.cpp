// #include "chess_game/chess.hpp"
// #include <iostream>
#include <cctype>
#include <utility>
#include <cstring>

using namespace std;

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



int main() {
    
    return 0;
}