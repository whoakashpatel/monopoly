#include "monopoly.hpp"

Game :: Game(int playerCount) : playerCount(playerCount) {
    for (int i = 0; i < playerCount; ++i) {
        string playerName;
        cout << "Enter name for player " << i + 1 << ": ";
        cin >> playerName;
        players.push_back(Player(i, playerName));
    }
    srand(time(0));
}

void Game :: play() {
    while (true) {
        for (Player &player : players) {
            cout << "------------------------------------------\n";
            cout << "player " << player.id + 1 << ": " << player.name << "'s chance --\n";
            
            cout << "rolling dice...\n";
            int rollResult = dice.roll();

            cout << "moving...\n";
            player.move(rollResult);
            cout << "player " << player.id + 1 << ": " << player.name << " has moved to tile " << player.currentLocation + 1 << ".\n";

            Tile *currentTile = board.tiles[player.currentLocation];
            currentTile->landOn(player, players);
            
            cout << "------------------------------------------\n";
            player.printDetails();

            cout << "------------------------------------------\n";
        }
    }
}