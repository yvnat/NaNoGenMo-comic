// main.cpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
// 

#include "simulator.hpp"
#include "elaborator.hpp"

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
    Elaborator e = Elaborator();
    PageSketch * sketch = e.elaborate(s.history[0]);
    if (sketch != nullptr) {
        PRINT("COUTING ELABORATION");
        cout << sketch->toString();
        PRINT("COUTED");
    }
    return 0;
}
