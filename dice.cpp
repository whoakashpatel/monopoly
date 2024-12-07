#include "monopoly.hpp"

Dice :: Dice() {
    srand(time(0));
}

int Dice :: roll() {
    for(int i = 0; i < 3; i++) {
        cout << ".";
        Sleep(600);
        // sleep(750) -- for unistd.h (linux)
    }
    
    int val = rand() % 6 + 1;
    cout << " got " << val << "\n";

    return val;
}