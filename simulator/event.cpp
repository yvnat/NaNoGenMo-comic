// event.cpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
// 

#include "event.hpp"

using namespace std;

Event::Event(EventType type) {
    this->type = type;
}

string Event::toString() {
    return to_string(type);
}