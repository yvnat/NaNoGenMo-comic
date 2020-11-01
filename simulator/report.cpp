// report.cpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
//

#include "report.hpp"

#include <iostream>

using namespace std;

Report::Report(TerrainType terrain, ActionType action, 
               Event * event, std::vector<Outcome *> outcomes)) {
    this->terrain = terrain;
    this->action = action;
    this->event = event;
    this->outcomes = outcomes;
}

void Report::test() {
    cout << "report.cpp\n";
}