#include "monopoly.hpp"

void Bank :: mortgageProperty(Player &player, vector<Player> &players) {
    cout << "Available cash: " << player.cash << "\n";
    cout << "You don't have enough cash! mortgaging a property...\n";
    cout << "------------------------------------------\n";

    if(player.propertiesBought.size() == 0) {
        cout << "You don't have enough cash to pay or properties to mortgage!\n";
        cout << "You're bankrupt!\n";
        cout << player.name << " is out of the game!...\n";
        player.cash = -1;
        return;
    }

    cout << "properties bought: ";
    for (Property &property : player.propertiesBought) {
        cout << property.name << "(" << property.price << ")" << " ";
    }
    cout << "\n";

    int propertyN = 0;
    cout << "Enter the property no. you want to mortgage (1-" << player.propertiesBought.size() << "): ";
    cin >> propertyN;
    while(propertyN < 1 || propertyN > player.propertiesBought.size()) {
        cout << "Enter valid property no.: ";
        cin >> propertyN;
    }
    propertyN--;

    player.cash += player.propertiesBought[propertyN].price / 2;
    player.propertiesBought[propertyN].owner = -2;
    player.propertiesMortgaged.push_back(player.propertiesBought[propertyN]);
    player.propertiesBought.erase(player.propertiesBought.begin() + propertyN);
}

void Bank :: renewMortgage(Player &player) {
    cout << "------------------------------------------\n";
    if(player.propertiesMortgaged.size() == 0) {
        cout << "You don't have any mortgaged properties!...\n";
        return;
    }
    
    cout << "properties mortgaged: ";
    for (Property &property : player.propertiesMortgaged) {
        cout << property.name << "(" << property.price << ")" << " ";
    }
    cout << "\n";

    int propertyN = 0;
    cout << "Enter the property no. you want to renew mortgage of (1-" << player.propertiesMortgaged.size() << "): ";
    cin >> propertyN;
    while(propertyN < 1 || propertyN > player.propertiesMortgaged.size()) {
        cout << "Enter valid property no.: ";
        cin >> propertyN;
    }
    propertyN--;

    if(player.cash < player.propertiesMortgaged[propertyN].price) {
        cout << "You don't have enough cash to renew the mortgage!...\n";
        return;
    }

    player.cash -= player.propertiesMortgaged[propertyN].price;
    player.propertiesMortgaged[propertyN].owner = player.id;
    player.propertiesBought.push_back(player.propertiesMortgaged[propertyN]);
    player.propertiesMortgaged.erase(player.propertiesMortgaged.begin() + propertyN);
}