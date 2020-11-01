// report.cpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
//

#include "report.hpp"

#include "misc.hpp"

#include <iostream>

using namespace std;

Report::Report(TerrainType terrain, ActionType action, 
               Event * event, std::vector<Outcome *> outcomes) {
    this->terrain = terrain;
    this->action = action;
    this->event = event;
    this->outcomes = outcomes;
    PRINT("Constructed Report");
}

void Report::debugPrint() {
    cout << "--Report " << this << "--\n";
    cout << "Terrain: " << terrain << "\n";
    cout << "Action: " << action << "\n";
    cout << "Event: " << event->toString() << "\n";
    cout << "Outcomes: \n";
    for (int i = 0; i < outcomes.size(); ++i) {
        cout << "    " << outcomes[i] << "\n";
    }
    cout << "--------------\n";
}