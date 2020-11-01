// report.hpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
// the report that summarizes a turn, and is then passed to the elaborator

#pragma once

#include "setting.hpp"
#include "event.hpp"
#include "outcome.hpp"

#include <vector>

class Report {
    public:
    
    TerrainType terrain;
    ActionType action;
    Event * event;
    std::vector<Outcome *> outcomes;

    void test();
};