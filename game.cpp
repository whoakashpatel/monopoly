#include "monopoly.hpp"

Game :: Game(int playerCount) : playerCount(playerCount) {
    while(this -> playerCount < 2 || this -> playerCount > 8) {
        cout << "Enter valid player count (2-8): ";
        cin >> this -> playerCount;
    }

    int initPlayerCash;
    cout << "Enter the amount of cash each player should start with: ";
    cin >> initPlayerCash;

    while(initPlayerCash < 5000) {
        cout << "Enter a valid amount (>=5000): ";
        cin >> initPlayerCash;
    }

    for (int i = 0; i < playerCount; ++i) {
        string playerName;
        cout << "Enter name for player " << i + 1 << ": ";
        cin >> playerName;
        players.push_back(Player(i, playerName, initPlayerCash));
    }
}

void Game :: play() {
    cout << "------------------------------------------\n";
    cout << "Starting the game";
    for(int i = 0; i < 4; i++) {
        cout << ".";
        Sleep(1000);
        // sleep(1000) -- for unistd.h (linux)
    }
    cout << "\n";
    cout << "------------------------------------------\n";

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
            
            cout << "------------------------------------------\n";

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

            cout << "------------------------------------------\n";

            for(int i = 0; i < 4; i++) {
                cout << ".";
                Sleep(1000);
                // sleep(1000) -- for unistd.h (linux)
            }
            cout << "\n";
        }
    }
}