// simulator.hpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
// 

#pragma once

#include "report.hpp"
#include "character.hpp"

#include <vector>

class Simulator {
    public:
    TerrainType currentTerrain;
    ActionType currentAction;
    int supplies;   //range 0-5
    int morale;     //range 0-5
    std::vector<Character *> characters;
    
    std::vector<Report *> history;

    Simulator();

    Report * simulateTurn();
};