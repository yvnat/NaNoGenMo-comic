// outcome.hpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
// 

#pragma once

enum OutcomeType {
    RELATIONSHIP_CHANGE,
    DISCONTENT_CHANGE,
    SUPPLIES_CHANGE,
};

class Outcome {
    OutcomeType type;
};

//and many child classes for the different outcome types