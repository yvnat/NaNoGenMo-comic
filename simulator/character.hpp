// character.hpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
// 

#pragma once

#include "relationship.hpp"

#include <string>
#include <vector>

class Relationship;

class Character {
    std::string name;
    std::vector<Relationship *> relationships;
};