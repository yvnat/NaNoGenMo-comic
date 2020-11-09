// pagesketch.cpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
//

#include "pagesketch.hpp"

using namespace std;

PageSketch::PageSketch(vector<Frame *> frames) {
    this->frames = frames;
}
PageSketch::~PageSketch() {
    for (int i = 0; i < frames.size(); ++i) {
        delete frames[i];
    }
}

string PageSketch::toString() {
    string toRet = "## PAGE ##################\n";
    for (int i = 0; i < frames.size(); ++i) {
        toRet += frames[i]->toString();
    }
    toRet += "##########################\n";
    return toRet;
}

string PageSketch::serialize() {
    string serialized = "["
    for (int i = 0; i < frames.size(); ++i) {
        if (i != 0) {
            serialized += ", ";
        }
        serialized += frames[i].serialize();
    }
    serialized += "]";
    return serialized;
}