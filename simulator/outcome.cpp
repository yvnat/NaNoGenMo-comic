// outcome.cpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
// 

#include "outcome.hpp"

using namespace std;

Outcome::Outcome(OutcomeType type) {
    this->type = type;
}
Outcome::~Outcome() {}

string Outcome::toString() {
    return "virtual";
}

////////////////////////////////////////////////////////////////////////////////

Outcome_Relationship::Outcome_Relationship(Relationship * affectedRelationship, 
        Justified<int> newOpinion)
         : Outcome::Outcome(OutcomeType::RELATIONSHIP_CHANGE) {
    this->affectedRelationship = affectedRelationship;
    this->newOpinion = newOpinion;
}
string Outcome_Relationship::toString() {
    return "Outcome Rltshp Chnge: "+affectedRelationship->owner->name+" to "
        +affectedRelationship->target->name +"; "
        +to_string(newOpinion.data)+" b/c "+newOpinion.justification;
}

////////////////////////////////////////////////////////////////////////////////

Outcome_Morale::Outcome_Morale(int change)
         : Outcome::Outcome(OutcomeType::MORALE_CHANGE) {
    this->change = change;
}
string Outcome_Morale::toString() {
    return "Outcome Morale Change: "+to_string(change);
}

////////////////////////////////////////////////////////////////////////////////

Outcome_Supplies::Outcome_Supplies(int change)
         : Outcome::Outcome(OutcomeType::SUPPLIES_CHANGE) {
    this->change = change;
}
string Outcome_Supplies::toString() {
    return "Outcome Supplies Change: "+to_string(change);
}