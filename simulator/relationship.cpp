// Relationship.cpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
// 

#include "relationship.hpp"

using namespace std;

Relationship::Relationship(Character * target) {
    this->target = target;
    this->opinions = {};
}

int Relationship::getTotalOpinion(Character * target) {
    int total = 0;
    for (int i = 0; i < opinions.size(); ++i) {
        total += opinions[i].data;
    }
    return total;
}

void Relationship::addOpinion(int value, string justification) {
    opinions.push_back(Justified<int>(value, justification));
}