// event.hpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
// 

#pragma once

enum EventType {
    TALK,
    ATTACKED
};

class Event {
    EventType type;
};