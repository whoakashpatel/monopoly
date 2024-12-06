#include "monopoly.hpp"

// Property Class Definitions

void Property :: landOn(Player &player, vector<Player> &players, Bank &bank) {
    cout << "You've arrived " << name << "!\n";
    if(owner == -2) {
        cout << "This property is mortgaged!, you needn't pay rent...\n";
    }
    else if(owner == -1) {
        if(player.cash >= price) {
            char ch;
            cout << "Do you want to buy " << name << " for " << price << "? You currently have " << player.cash << ", (y/n): ";
            cin >> ch;
            if(ch == 'y') {
                player.cash -= price;
                owner = player.id;
                player.propertiesBought.push_back(*this);
                cout << "Congrats, you've bought " << name << "!\n";
                checkMonopoly(player);
            }
        }
        else {
            cout << "You don't have enough cash to buy " << name << "!\n";
        }
    }
    else {
        int reqdRent = (1 + players[owner].hasMonopoly) * rent;
        cout << "This place is owned, you need to pay a rent of " << reqdRent << " to " << players[owner].name << ".\n";
        if(player.cash < reqdRent) {
            bank.mortgageProperty(player, players);
        }
        if(player.cash > 0) {
            player.cash -= reqdRent;
            players[owner].cash += reqdRent;
        }
    }
}

bool Property :: checkMonopoly(Player &player) {
    map<string, int> colorCount;
    for (Property property : player.propertiesBought) {
        colorCount[property.color]++;
    }
    for (auto &entry : colorCount) {
        if (entry.second == 5) {
            player.hasMonopoly = true;
            break;
        }
    }
}

// Jail Class Definitions

void Jail :: landOn(Player &player, vector<Player> &players, Bank &bank) {
    cout << "OOPS you ran into jail for a crime!\n";
    cout << "You will be charged with " << fine << " fine!\n";
    if(player.cash < fine) {
        bank.mortgageProperty(player, players);
    }
    player.cash -= fine;
}

// Chance Class Definitions

Chance :: Chance() {
    chances = {"Win lottery 1000",
                "Pay 500 fine",
                "Move forward 10 steps",
                "Go to Jail & pay 500 fine",
                "Pay 250 to everyone for community contribution",
                "Pay 500 Income Tax",
                "Go back 10 steps",
                "Collect 500 from bank"};
}

void Chance :: landOn(Player &player, vector<Player> &players, Bank &bank) {
    cout << "You've landed on a chance block\n";
    cout << "Picking a random chance...\n";
    int index = rand() % chances.size();
    cout << "Chance received: " << chances[index] << "\n";
    switch(index) {
        case 0:
            player.cash += 1000;
            break;
        case 1:
            if(player.cash < 500) {
                bank.mortgageProperty(player, players);
            }
            player.cash -= 500;
            break;
        case 2:
            player.move(10);
            break;
        case 3:
            player.currentLocation = 10;
            if(player.cash < 500) {
                bank.mortgageProperty(player, players);
            }
            player.cash -= 500;
            break;
        case 4:
            if(player.cash < 250 * players.size() - 1) {
                bank.mortgageProperty(player, players);
            }
            for(Player &player : players) {
                if(player.id != player.id) {
                    player.cash += 250;
                    player.cash -= 250;
                }
            }
            break;
        case 5:
            if(player.cash < 500) {
                bank.mortgageProperty(player, players);
            }
            player.cash -= 500;
            break;
        case 6:
            player.move(-10);
            break;
        case 7:
            player.cash += 500;
            break;
    }
}

// IncomeTax Class Definitions

void IncomeTax :: landOn(Player &player, vector<Player> &players, Bank &bank) {
    cout << "You are required to pay " << (player.hasPaidTax ? subsequentTax : firstTimeTax) << " as tax to the Bank.\n";
    if(player.hasPaidTax) {
        if(player.cash < subsequentTax) {
            bank.mortgageProperty(player, players);
        }
        player.cash -= subsequentTax;
    }
    else {
        if(player.cash < firstTimeTax) {
            bank.mortgageProperty(player, players);
        }
        player.cash -= firstTimeTax;
        player.hasPaidTax = true;
    }
}