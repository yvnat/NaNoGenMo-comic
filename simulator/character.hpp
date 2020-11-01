// character.hpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
// 

#pragma once

#include "relationship.hpp"

#include <string>
#include <vector>

class Relationship;

class Character {
    public:
    std::string name;
    std::vector<Relationship *> relationships;

    Character();
    ~Character();

    private:
    std::vector<std::string> loadNamesFromFile(std::string filename);
};