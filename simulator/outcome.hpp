// outcome.hpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
// 

#pragma once

#include "misc.hpp"
#include "relationship.hpp"

#include <string>

enum OutcomeType {
    RELATIONSHIP_CHANGE,
    MORALE_CHANGE,
    SUPPLIES_CHANGE,
};

class Outcome {
    /**
     * Generic outcome
     */
    public:
    OutcomeType type;

    Outcome(OutcomeType type);
    virtual ~Outcome();

    virtual std::string toString();
};

class Outcome_Relationship : public Outcome {
    /**
     * In this outcome, a relationship is changed
     */
    public:
    Relationship * affectedRelationship;
    Justified<int> newOpinion;

    Outcome_Relationship(Relationship * affectedRelationship, 
                         Justified<int> newOpinion);

    std::string toString();
};

class Outcome_Morale : public Outcome {
    /**
     * In this outcome, the hoplites' morale changes
     */
    public:
    int change; //the change in morale

    Outcome_Morale(int change);

    std::string toString();
};

class Outcome_Supplies : public Outcome {
    /**
     * In this outcome, the supply situation changes
     */
    public:
    int change; //the change in supplies

    Outcome_Supplies(int change);

    std::string toString();
};