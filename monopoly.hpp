#ifndef MONOPOLY_H
#define MONOPOLY_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <chrono>
#include <thread>

using namespace std;


class Dice {
    public:
        Dice();
        int roll();
};


class Property;


class Player {
    private:
        int id;
        string name;
        int currentLocation = 0;
        int cash;
        vector<Property> propertiesBought;
        vector<Property> propertiesMortgaged;
        bool hasMonopoly = false;
        bool hasPaidTax = false;

    public:
        Player(int id, string name, int initPlayerCash) : id(id), name(name), cash(initPlayerCash) {}
        void move(int steps);
        void printDetails();

    friend class Bank;
    friend class Property;
    friend class Jail;
    friend class Chance;
    friend class IncomeTax;
    friend class Game;
};


class Bank;


class Tile {
    protected:
        virtual void landOn(Player &player, vector<Player> &players, Bank &bank) = 0;

    friend class Game;
};


class Property : public Tile {
    private:
        string name;
        string color;
        int price;
        int rent;
        int owner;

    public:
        Property(string name, string color, int price, int rent) : name(name), color(color), price(price), rent(rent), owner(-1) {}
        void landOn(Player &player, vector<Player> &players, Bank &bank) override;
        bool checkMonopoly(Player &player);

    friend class Bank;
    friend class Player;
    friend class Game;
};


class Jail : public Tile {
    private:
        int fine;

    public:
        Jail(int fine) : fine(fine) {}
        void landOn(Player &player, vector<Player> &players, Bank &bank) override;
};


class Chance : public Tile {
    private:
        vector<string> chances;

    public:
        Chance();
        void landOn(Player &player, vector<Player> &players, Bank &bank) override;
};


class IncomeTax : public Tile {
    private:
        int firstTimeTax;
        int subsequentTax;

    public:
        IncomeTax(int firstTimeTax, int subsequentTax) : firstTimeTax(firstTimeTax), subsequentTax(subsequentTax) {}
        void landOn(Player &player, vector<Player> &players, Bank &bank) override;
};


class Bank {
    public:
        void mortgageProperty(Player &player, vector<Player> &players);
        void renewMortgage(Player &player);
};


class Board {
    private:
        vector<Tile*> tiles;
        vector<Player> players;

    public:
        Board();

    friend class Game;
};


class Game {
    private:
        int playerCount;
        vector<Player> players;
        Board board;
        Dice dice;
        Bank bank;

    public:
        Game(int playerCount = 2);
        void play();
};

#endif