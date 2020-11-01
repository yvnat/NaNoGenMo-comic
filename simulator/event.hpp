// event.hpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
// 

#pragma once

#include <string>

enum EventType {
    TALK,
    ATTACKED
};

class Event {
    public:
    EventType type;

    Event(EventType type);

    std::string toString();
};