// character.hpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
// 

#pragma once

#include "relationship.hpp"

#include <string>
#include <vector>
#include <unordered_map>

class Relationship;

class CharacterAppearance {
    public:
    //a class that will eventually contain information related to the current
    //appearance of a character; boilerplate for now
    bool isArmed;
    std::vector<int> colour;
    CharacterAppearance(bool isArmed, std::vector<int> colour);
    CharacterAppearance();
    ~CharacterAppearance();

    std::string serialize();
};

class Character {
    public:
    CharacterAppearance appearance;
    std::string name;
    std::unordered_map<Character *, Relationship *> relationships;

    Character();
    ~Character();

    Relationship * getRelationship(Character * character);

    private:
    std::vector<std::string> loadNamesFromFile(std::string filename);
};