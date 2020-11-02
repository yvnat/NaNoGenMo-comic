// Relationship.hpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
// 

#pragma once

#include "character.hpp"
#include "misc.hpp"

#include <vector>

class Character;

class Relationship {
    public:
    Character * target; //the character towards whom the relationship is
    Character * owner;  //the character from whom it originates
    std::vector<Justified<int>> opinions;

    Relationship(Character * owner, Character * target);
    ~Relationship();

    void addOpinion(int value, std::string justification);
    void addOpinion(Justified<int>);
    int getTotalOpinion(Character * target);
};