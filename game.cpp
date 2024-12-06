#include "monopoly.hpp"

Game :: Game(int playerCount) : playerCount(playerCount) {
    if(playerCount < 2 || playerCount > 8) {
        cout << "Invalid player count, setting player count to 2...\n";
        playerCount = 2;
    }

    int initPlayerCash;
    cout << "Enter the amount of cash each player should start with: ";
    cin >> initPlayerCash;

    for (int i = 0; i < playerCount; ++i) {
        string playerName;
        cout << "Enter name for player " << i + 1 << ": ";
        cin >> playerName;
        players.push_back(Player(i, playerName, initPlayerCash));
    }
}

void Game :: play() {
    while (true) {
        for (Player &player : players) {
            if(player.cash < 0) {
                for(Property& prop : player.propertiesMortgaged) {
                    prop.owner = -1;
                }
                for(int i = player.id + 1; i < players.size(); i++) {
                    for(Property& prop : players[i].propertiesBought) {
                        prop.owner -= 1;
                    }
                    players[i].id -= 1;
                }

                players.erase(players.begin() + player.id);

                continue;
            }

            if(players.size() < 2) {
                cout << "*********************************\n";
                cout << "The winner is: " << players[0].name << "!\n";
                cout << "*********************************\n";
                return;
            }

            cout << "------------------------------------------\n";

            cout << player.name << "'s chance --\n";

            cout << "------------------------------------------\n";
            
            cout << "rolling dice: ";
            int rollResult = dice.roll();

            player.move(rollResult);
            cout << player.name << " has moved to tile " << player.currentLocation + 1 << ".\n";

            Tile *currentTile = board.tiles[player.currentLocation];
            currentTile->landOn(player, players, bank);

            if (player.cash >= 0) {
                int minRenewalPrice = INT_MAX;
                for(Property prop : player.propertiesMortgaged)
                    minRenewalPrice = min(minRenewalPrice, prop.price);
                
                Property* isProp = dynamic_cast<Property*>(currentTile);
                if(isProp && player.propertiesMortgaged.size() > 0 && player.cash > minRenewalPrice) {
                    char ch;
                    cout << "Available cash: " << player.cash << "\n";
                    cout << "Would you like to reclaim any of your properties (y/n): ";
                    cin >> ch;
                    if(ch == 'y') {
                        bank.renewMortgage(player);
                    }
                }

                cout << "------------------------------------------\n";
                player.printDetails();
            }

            cout << "------------------------------------------\n\n";

            /* for(int i = 0; i < 4; i++) {
                cout << ".";
                this_thread::sleep_for(chrono::milliseconds(750));
            }
            cout << "\n"; */
        }
    }
}