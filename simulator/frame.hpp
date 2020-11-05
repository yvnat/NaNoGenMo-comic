// frame.hpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
// an assortment of classes related to a single frame

#pragma once

#include "character.hpp"

#include <string>
#include <vector>

class CharacterAction {
    /**
     * Represents a character's pose and dialogue
     */
    public:
    CharacterAction(Character * character, std::string pose, std::string dialogue);
    ~CharacterAction();

    Character * character;
    std::string pose;           //path to pose file
    std::string dialogue;       //the line of dialogue this character says
};

class Frame {
    /**
     * A single frame of the comic
     */
    public:
    Frame(std::vector<CharacterAction> actions);
    ~Frame();

    std::vector<CharacterAction> actions;

    std::string toString();
};