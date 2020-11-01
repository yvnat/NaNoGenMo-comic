// outcome.hpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
// 

#pragma once

enum OutcomeType {
    RELATIONSHIP_CHANGE,
    MORALE_CHANGE,
    SUPPLIES_CHANGE,
};

class Outcome {
    public:
    OutcomeType type;

    Outcome(OutcomeType type);
};

//and many child classes for the different outcome types