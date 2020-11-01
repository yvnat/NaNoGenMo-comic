// character.cpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
// 

#include "character.hpp"

#include "misc.hpp"

Character::Character() {
    this->name = rng::randomGenericName(6);
    this->relationships = {};
    PRINT("Constructed character " + name);
}

Character::~Character() {
    for (int i = relationships.size()-1; i >= 0; --i) {
        delete relationships[i];
    }
    PRINT("Destroyed character " + name);
}