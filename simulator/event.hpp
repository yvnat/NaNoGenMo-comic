// event.hpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
// 

#pragma once

#include "character.hpp"

#include <string>
#include <vector>

enum EventType {
    TALK,
    ATTACKED
};

class Event {
    public:
    EventType type;

    Event(EventType type);

    virtual std::string toString();
};

class EventTalk : public Event {
    public:
    std::vector<Character *> participants;
    EventTalk(std::vector<Character *> participants);
};