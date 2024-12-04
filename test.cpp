#include "monopoly.hpp"

/*
    Do - 'g++ test.cpp monopoly.cpp board.cpp dice.cpp bank.cpp player.cpp tile.cpp' to compile.
*/

/*
    I've also not yet added the logic for checking if
    a player is bankrupt & eventually checking if only
    1 player is available to play & thus is the winner.
    I'll do it in the final version.
 */

int main() {
    int n;
    cout << "Enter no. of players: ";
    cin >> n;

    Game game(n);
    game.play();

    return 0;
}