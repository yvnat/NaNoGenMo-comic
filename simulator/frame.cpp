// frame.cpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
// 

#include "frame.hpp"
#include "misc.hpp"

using namespace std;

CharacterAction::CharacterAction(Character * character, std::string pose, 
        std::string dialogue) {
    this->character = character;
    this->pose = pose;
    this->dialogue = dialogue;
}
CharacterAction::~CharacterAction() {

}

Frame::Frame(std::vector<CharacterAction> actions) {
    PRINT("Constructed frame");
    this->actions = actions;
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