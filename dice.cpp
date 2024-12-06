#include "monopoly.hpp"

Dice :: Dice() {
    srand(time(0));
}

int Dice :: roll() {
    /* for(int i = 0; i < 4; i++) {
        cout << ".";
        this_thread::sleep_for(chrono::milliseconds(750));
    }
    cout << "\n"; */
    
    int val = rand() % 6 + 1;
    cout << "got " << val << "\n";
    return val;
}