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
    Character * target;
    std::vector<Justified<int>> opinions;

    Relationship(Character * target);

    void addOpinion(int value, std::string justification);
    int getTotalOpinion(Character * target);
};