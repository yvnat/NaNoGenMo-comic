// main.cpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
// 

#include "simulator.hpp"

#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
    Simulator s = Simulator();
    s.simulateTurn();
    s.simulateTurn();
    s.simulateTurn();
    s.simulateTurn();
    s.simulateTurn();
    s.simulateTurn();
    for (int i = 0; i < s.history.size(); ++i) {
        s.history[i]->debugPrint();
    }
    Character c = Character();
    return 0;
}
