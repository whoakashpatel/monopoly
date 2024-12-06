#include "monopoly.hpp"

/*
    Do - 'g++ test.cpp game.cpp board.cpp dice.cpp bank.cpp player.cpp tile.cpp' to compile.
*/


int main() {
    int n;
    cout << "Enter no. of players: ";
    cin >> n;

    Game game(n);
    game.play();

    return 0;
}