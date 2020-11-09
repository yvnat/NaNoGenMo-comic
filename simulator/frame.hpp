// frame.hpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
// an assortment of classes related to a single frame

#pragma once

#include "character.hpp"

#include <string>
#include <vector>

#define DIRECTION_RIGHT true
#define DIRECTION_LEFT false

class CharacterAction {
    /**
     * Represents a character's pose and dialogue
     */
    public:
    CharacterAction(Character * character, std::string pose, 
        std::string dialogue, double positionX, double positionY, double size, 
        bool direction);
    ~CharacterAction();

    Character * character;
    CharacterAppearance appearance;
    std::string pose;           //path to pose file
    std::string dialogue;       //the line of dialogue this character says

    double positionX, positionY;    //position, in % of frame dimensions
    double size;                    //size, in SFU (1 SFU = 1 normal frame size)
    bool direction;                 //true = right facing, false = left facing
};

class Frame {
    /**
     * A single frame of the comic
     */
    public:
    Frame(std::vector<CharacterAction> actions);
    ~Frame();

    double sizeX, sizeY;        //size, in SFU

    std::vector<CharacterAction> actions;

    std::string toString();
};