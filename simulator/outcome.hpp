// outcome.hpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
// 

#pragma once

#include <string>

enum OutcomeType {
    RELATIONSHIP_CHANGE,
    MORALE_CHANGE,
    SUPPLIES_CHANGE,
};

class Outcome {
    public:
    OutcomeType type;

    Outcome(OutcomeType type);

    std::string toString();
};

//and many child classes for the different outcome types