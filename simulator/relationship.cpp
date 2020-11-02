// Relationship.cpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
// 

#include "relationship.hpp"

using namespace std;

Relationship::Relationship(Character * owner, Character * target) {
    this->owner = owner;
    this->target = target;
    this->opinions = {};
    PRINT("Constructed relationship");
}
Relationship::~Relationship() {
    PRINT("Destroyed relationship");
}

int Relationship::getTotalOpinion(Character * target) {
    int total = 0;
    for (int i = 0; i < opinions.size(); ++i) {
        total += opinions[i].data;
    }
    return total;
}

void Relationship::addOpinion(Justified<int> opinion) {
    opinions.push_back(opinion);
}
void Relationship::addOpinion(int value, string justification) {
    opinions.push_back(Justified<int>(value, justification));
}