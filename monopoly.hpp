#ifndef MONOPOLY_H
#define MONOPOLY_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cstdlib>
#include <ctime>

using namespace std;

class Dice {
    public:
        int roll();
};

class Property;

class Player {
    public:
        int id;
        string name;
        int currentLocation;
        int cash;
        vector<Property*> propertiesBought;
        vector<Property*> propertiesMortgaged;
        // map<int, int> denominations; // will implement having different denominations for Player class later
        bool hasMonopoly;
        bool hasPaidTax;

        Player(int id, string name) : id(id), name(name), currentLocation(0), cash(15000), hasMonopoly(false) {}
        void move(int steps);
        void printDetails();
};

// I'm using Tile as an abstract class here, although I might add attributes/methods later
class Tile {
    public:
        virtual void landOn(Player &p, vector<Player> &players) = 0;
};

class Property : public Tile {
    public:
        string name;
        string color;
        int price;
        int rent;
        int owner;

        Property(string name, string color, int price, int rent) : name(name), color(color), price(price), rent(rent), owner(-1) {}
        void landOn(Player &p, vector<Player> &players) override;
        bool checkMonopoly(Player &p);
};

class Jail : public Tile {
    public:
        int fine;

        Jail(int fine) : fine(fine) {}
        void landOn(Player &p, vector<Player> &players) override;
};

class Chance : public Tile {
    public:
        vector<string> chances;

        Chance();
        void landOn(Player &p, vector<Player> &players) override;
};

class IncomeTax : public Tile {
    public:
        int firstTimeTax;
        int subsequentTax;

        IncomeTax(int firstTimeTax, int subsequentTax) : firstTimeTax(firstTimeTax), subsequentTax(subsequentTax) {}
        void landOn(Player &p, vector<Player> &players) override;
};

/*
    class Bank {
    public:
        map<int, int> denominations;

        Bank() {
            denominations[10000] = 10;
            denominations[1000] = 20;
            denominations[500] = 30;
            denominations[100] = 50;
            denominations[50] = 100;
        }

        void provideChange(int amount) {
            // will finish this in final version
        }
    };
*/

class Board {
    public:
        vector<Tile*> tiles;
        vector<Player> players;

        Board();
};

class Game {
    public:
        int playerCount;
        vector<Player> players;
        Board board;
        Dice dice;
        // Bank bank; // will implement later

        Game(int playerCount = 2);
        void play();
};

#endif