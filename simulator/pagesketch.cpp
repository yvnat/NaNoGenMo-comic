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
    PRINT("");
    string toRet = "";
    for (int i = 0; i < frames.size(); ++i) {
        PRINT("");
        toRet += frames[i]->toString();
    }
    return toRet;
}