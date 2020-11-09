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

CharacterAction::CharacterAction(Character * character, std::string pose, 
        std::string dialogue, CharacterActionPosition position) {
    this->character = character;
    this->appearance = character->appearance;
    this->pose = pose;
    this->dialogue = dialogue;

    this->position = position;
}
CharacterAction::~CharacterAction() {

}

FrameBackground::FrameBackground(std::vector<int> skyColour, 
        std::vector<int> groundColour, double horizonHeight) {
    this->skyColour = skyColour;
    this->groundColour = groundColour;
    this->horizonHeight= horizonHeight;
}
FrameBackground::FrameBackground() {};

FrameBackground::~FrameBackground() {}

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
string Frame::toString() {
    string toRet = "--Frame:--\n";
    for (int i = 0; i < actions.size(); ++i) {
        toRet += actions[i].character->name+" ["+actions[i].pose+"]: "
                 + actions[i].dialogue + "\n";
    }
    toRet += "\n";
    return toRet;
}