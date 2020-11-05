// event.cpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
// 

#include "event.hpp"

using namespace std;

Event::Event(EventType type) {
    this->type = type;
}

string Event::toString() {
    string sEnum[] = {"TALK","ATTACKED"};
    return sEnum[type];
}

EventTalk::EventTalk(std::vector<Character *> participants) : Event(EventType::TALK) {
    this->participants = participants;
}