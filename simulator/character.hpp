// character.hpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
// 

#pragma once

#include "relationship.hpp"

#include <string>
#include <vector>
#include <unordered_map>

class Relationship;

class Character {
    public:
    std::string name;
    std::unordered_map<Character *, Relationship *> relationships;

    Character();
    ~Character();

    Relationship * getRelationship(Character * character);

    private:
    std::vector<std::string> loadNamesFromFile(std::string filename);
};