// outcome.cpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
// 

#include "outcome.hpp"

using namespace std;

Outcome::Outcome(OutcomeType type) {
    this->type = type;
}

string Outcome::toString() {
    string sEnum[] = {"RELATIONSHIP_CHANGE","MORALE_CHANGE","SUPPLIES_CHANGE"};
    return sEnum[type];
}