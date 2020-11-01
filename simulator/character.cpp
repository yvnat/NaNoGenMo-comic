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