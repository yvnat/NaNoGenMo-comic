// elaborator.cpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
//

#include "elaborator.hpp"

#define ELABORATOR_DESIRED_FRAMES 6

using namespace std;

Elaborator::Elaborator() {

}
Elaborator::~Elaborator() {

}

PageSketch * Elaborator::elaborate(Report * report) {
    if (report->event->type == EventType::TALK) {
        return elaborateTalk(report);
    } else if (report->event->type == EventType::ATTACKED) {
        return elaborateBattle(report);
    }
    PRINT("***ELABORATOR: UNSUPPORTED EVENT TYPE");
    return nullptr;
}

PageSketch * Elaborator::elaborateTalk(Report * report) {
    int desiredFrames = ELABORATOR_DESIRED_FRAMES;
    vector<Frame *> frames = {};
    int framesNeeded = desiredFrames - frames.size();
    EventTalk * event = dynamic_cast<EventTalk *>(report->event);

    while (framesNeeded > 0) {
        /* 
        if (framesNeeded > 1 and (frames.size()==0)?(high chance):(low chance)) {
            frames.add(makeFrame(getQuestion));
            frames.add(makeFrame(getAnswer));
        }
         */
        vector<CharacterAction> actions = {};

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

PageSketch * Elaborator::elaborateBattle(Report * report) {
    int desiredFrames = ELABORATOR_DESIRED_FRAMES;
    vector<Frame *> frames = {};
    int framesNeeded = desiredFrames - frames.size();
    EventBattle * event = dynamic_cast<EventBattle *>(report->event);

    while (framesNeeded > 0) {
        vector<CharacterAction> actions = {};

        if (framesNeeded == 1) {
            string dialogue = "***";
            if (event->won) {
                dialogue = "We won the battle yay";
            } else {
                dialogue = "We lost much supply in this raid oh no";
            }
            actions.push_back(CharacterAction(event->participants[0], "stand", dialogue));
        } else {
            actions.push_back(CharacterAction(rng::randElement(event->participants), "strike", ""));
        }
        frames.push_back(new Frame(actions));
        framesNeeded = desiredFrames - frames.size();
    }

    return new PageSketch(frames);
}