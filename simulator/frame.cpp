// frame.cpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
// 

#include "frame.hpp"
#include "misc.hpp"

using namespace std;

CharacterActionPosition::CharacterActionPosition(double positionX, 
        double positionY, double size, bool direction) {
    this->positionX = positionX;
    this->positionY = positionY;
    this->size = size;
    this->direction = direction;
}
CharacterActionPosition::CharacterActionPosition() {}
CharacterActionPosition::~CharacterActionPosition() {}
string CharacterActionPosition::serialize() {
    return "["+to_string(positionX)+", "+to_string(positionY)+", "+
            to_string(size)+", "+to_string(direction)+"]";
}

////////////////////////////////////////////////////////////////////////////////

CharacterAction::CharacterAction(Character * character, std::string pose, 
        std::string dialogue, CharacterActionPosition position) {
    this->character = character;
    
    this->pose = pose;
    this->dialogue = dialogue;
    this->position = position;
    this->appearance = character->appearance;
}
CharacterAction::~CharacterAction() {

}

string CharacterAction::serialize() {
    return "[\""+pose+"\", \""+dialogue+"\", "+
            position.serialize()+", "+appearance.serialize()+"]";
}

////////////////////////////////////////////////////////////////////////////////

FrameBackground::FrameBackground(std::vector<int> skyColour, 
        std::vector<int> groundColour, double horizonHeight) {
    this->skyColour = skyColour;
    this->groundColour = groundColour;
    this->horizonHeight= horizonHeight;
}
FrameBackground::FrameBackground() {
    FrameBackground({77,195,255}, {100,200,0}, .5);
};

FrameBackground::~FrameBackground() {}

string FrameBackground::serialize() {
    return "[["+to_string(skyColour[0])+","
               +to_string(skyColour[1])+","
               +to_string(skyColour[2])
            +"], ["
               +to_string(groundColour[0])+","
               +to_string(groundColour[1])+","
               +to_string(groundColour[2])
            +"], "+to_string(horizonHeight)+"]";
}

////////////////////////////////////////////////////////////////////////////////

Frame::Frame(std::vector<CharacterAction> actions, FrameBackground background) {
    PRINT("Constructed frame");
    this->actions = actions;
    this->sizeX = 1;
    this->sizeY = 1;
    this->background = background;
}
Frame::~Frame() {
    PRINT("Destroyed frame");
}
string Frame::serialize() {
    string serializedActions = "[";
    for (int i = 0; i < actions.size(); ++i) {
        if (i != 0) {
            serializedActions += ", ";
        }
        serializedActions += actions[i].serialize();
    }
    serializedActions += "]";
    return "["+to_string(sizeX)+", "+to_string(sizeY)+", "
            +serializedActions+", "+background.serialize()+"]";
}
string Frame::toString() {
    string toRet = "--Frame:--\n";
    for (int i = 0; i < actions.size(); ++i) {
        toRet += actions[i].character->name+" ["+actions[i].pose+"]: "
                 + actions[i].dialogue + "\n";
    }
    toRet += "\n";
    return toRet;
}