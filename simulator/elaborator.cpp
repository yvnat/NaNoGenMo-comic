// elaborator.cpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
//

#include "elaborator.hpp"

using namespace std;

Elaborator::Elaborator() {

}
Elaborator::~Elaborator() {

}

PageSketch * Elaborator::elaborate(Report * report) {
    if (report->event->type == EventType::TALK) {
        return elaborateTalk(report);
    }
    return nullptr;
}

PageSketch * Elaborator::elaborateTalk(Report * report) {
    /* interrogation-style conversation */
    /* 
    desiredFrames = ???
    frames = {}
    framesNeeded = frames.size() - desiredFrames;
    while (framesNeeded > 0) {
        if (framesNeeded > 1 and (frames.size()==0)?(high chance):(low chance)) {
            frames.add(makeFrame(getQuestion));
            frames.add(makeFrame(getAnswer));
        }
        frames.add(makeFrame(getQuestion, getAnswer));
    }
     */
    int desiredFrames = 6;
    vector<Frame *> frames = {};
    int framesNeeded = desiredFrames - frames.size();
    while (framesNeeded > 0) {
        PRINT("");
        // if (framesNeeded > 1) {

        // }
        vector<CharacterAction> actions = {};

        EventTalk * event = dynamic_cast<EventTalk *>(report->event);

        CharacterAction question = getNextQuestion(event->participants[0], event->participants[1]);
        CharacterAction answer = answerQuestion(question, event->participants[0], event->participants[1]);
        actions.push_back(question);
        actions.push_back(answer);

        Frame * frame = new Frame(actions);
        frames.push_back(frame);
        framesNeeded = desiredFrames - frames.size();
    }
    return new PageSketch(frames);
}

CharacterAction Elaborator::getNextQuestion(Character * asker, 
        Character * answerer) {
    return CharacterAction(asker, "question", "?");
}
CharacterAction Elaborator::answerQuestion(CharacterAction question, Character * asker, 
        Character * answerer) {
    return CharacterAction(answerer, "explaining2", "!");
}