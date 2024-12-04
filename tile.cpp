#include "monopoly.hpp"

// Property Class Definitions

void Property :: landOn(Player &p, vector<Player> &players) {
    cout << "You've arrived " << name << "!\n";
    if(owner == -1) {
        if(p.cash >= price) {
            char ch;
            cout << "Do you want to buy " << name << " for " << price << "? You currently have " << p.cash << ", (y/n): ";
            cin >> ch;
            if(ch == 'y') {
                p.cash -= price;
                owner = p.id;
                p.propertiesBought.push_back(this);
                cout << "Congrats, you've bought " << name << "!\n";
                checkMonopoly(p);
            }
        }
    } else {
        int reqdRent = (1 + players[owner].hasMonopoly) * rent;
        cout << "This place is owned, you need to pay a rent of " << reqdRent << " to " << players[owner].name << ".\n";
        p.cash -= reqdRent;
        players[owner].cash += reqdRent;
    }
}

bool Property :: checkMonopoly(Player &p) {
    map<string, int> colorCount;
    for (Property* property : p.propertiesBought) {
        colorCount[property->color]++;
    }
    for (auto &entry : colorCount) {
        if (entry.second == 5) {
            p.hasMonopoly = true;
            break;
        }
    }
}

// Jail Class Definitions

void Jail :: landOn(Player &p, vector<Player> &players) {
    cout << "OOPS you ran into jail for a crime!\n";
    cout << "You will be charged with " << fine << " fine!\n";
    p.cash -= fine;
}

// Chance Class Definitions

Chance :: Chance() {
    chances = {"Win lottery 1000",
                "Pay 500 fine",
                "Move forward 10 steps",
                "Go to Jail",
                "Pay 250 to everyone for community contribution",
                "Pay 500 Income Tax",
                "Go back 10 steps",
                "Collect 500 from bank"};
}

void Chance :: landOn(Player &p, vector<Player> &players) {
    cout << "You've landed on a chance block\n";
    cout << "Picking a random chance...\n";
    int index = rand() % chances.size();
    cout << "Chance received: " << chances[index] << '\n';
    switch(index) {
        case 0:
            p.cash += 1000;
            break;
        case 1:
            p.cash -= 500;
            break;
        case 2:
            p.move(10);
            break;
        case 3:
            p.currentLocation = 10;
            break;
        case 4:
            for(Player &player : players) {
                if(player.id != p.id) {
                    player.cash += 250;
                    p.cash -= 250;
                }
            }
            break;
        case 5:
            p.cash -= 500;
            break;
        case 6:
            p.move(-10);
            break;
        case 7:
            p.cash += 500;
            break;
    }
}

// IncomeTax Class Definitions

void IncomeTax :: landOn(Player &p, vector<Player> &players) {
    cout << "You are required to pay " << (p.hasPaidTax ? subsequentTax : firstTimeTax) << " as tax to the Bank.\n";
    if(p.hasPaidTax) {
        p.cash -= subsequentTax;
    } else {
        p.cash -= firstTimeTax;
        p.hasPaidTax = true;
    }
}