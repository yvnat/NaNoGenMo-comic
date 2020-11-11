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
    std::vector<PageSketch *> sketches = {};
    for (int i = 0; i < s.history.size(); ++i) {
        PageSketch * sketch = e.elaborate(s.history[i]);
        sketches.push_back(sketch);
    }
    for (int i = 0; i < sketches.size(); ++i) {
        cout << sketches[i]->toString();
    }
    for (int i = 0; i < sketches.size(); ++i) {
        cout << sketches[i]->serialize() << "\n";
    }
    for (int i = 0; i < sketches.size(); ++i) {
        delete sketches[i];
        sketches[i] = nullptr;
    }
    return 0;
}
