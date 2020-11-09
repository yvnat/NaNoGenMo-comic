// frame.hpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
// an assortment of classes related to a single frame

#pragma once

#include "character.hpp"

#include <string>
#include <vector>

#define DIRECTION_RIGHT true
#define DIRECTION_LEFT false

class CharacterActionPosition {
    public:
    double positionX, positionY;    //position, in % of frame dimensions
    double size;                    //size, in SFU (1 SFU = 1 normal frame size)
    bool direction;                 //true = right facing, false = left facing

    CharacterActionPosition(double positionX, double positionY, double size, 
        bool direction);
    CharacterActionPosition();
    ~CharacterActionPosition();
};

class CharacterAction {
    /**
     * Represents a character's pose and dialogue
     */
    public:
    CharacterAction(Character * character, std::string pose, 
        std::string dialogue, CharacterActionPosition position);
    ~CharacterAction();

    Character * character;
    CharacterAppearance appearance;
    std::string pose;           //path to pose file
    std::string dialogue;       //the line of dialogue this character says

    CharacterActionPosition position;
};

class FrameBackground {
    /**
     * The background of a frame.
     * Currently encodes the colours of the sky and ground, and the horizon's y.
     */
    public:
    std::vector<int> skyColour; 
    std::vector<int> groundColour;
    double horizonHeight;            //in frame %
    FrameBackground(std::vector<int> skyColour, std::vector<int> groundColour,
            double horizonHeight);
    FrameBackground();
    ~FrameBackground();
};

class Frame {
    /**
     * A single frame of the comic
     */
    public:
    Frame(std::vector<CharacterAction> actions, FrameBackground background=FrameBackground({77,195,255}, {100,200,0}, .5));
    ~Frame();

    double sizeX, sizeY;        //size, in SFU
    FrameBackground background;
    std::vector<CharacterAction> actions;

    std::string toString();
};