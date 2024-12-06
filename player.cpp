#include "monopoly.hpp"

void Player :: move(int steps) {
    currentLocation = (currentLocation + steps) % 40;
}

void Player :: operator++() {
    move(1);
}

void Player :: operator+=(int steps) {
    move(steps);
}

void Player :: printDetails() {
    cout << name << " on tile " << currentLocation + 1 << "\n";
    cout << "available cash: " << cash << "\n";

    cout << "properties bought: ";
    for (Property &property : propertiesBought) {
        cout << property.name << " ";
    }
    cout << "\n";

    cout << "properties mortgaged: ";
    for (Property &property : propertiesMortgaged) {
        cout << property.name << " ";
    }
    cout << "\n";
}