#include "monopoly.hpp"

int Dice :: roll() {
    int val = rand() % 6 + 1;
    cout << "got " << val << '\n';
    return val;
}