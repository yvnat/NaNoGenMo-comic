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

        Frame * frame = t_facing(question, answer);
        frames.push_back(frame);
        framesNeeded = desiredFrames - frames.size();
    }
    return new PageSketch(frames);
}

CharacterAction Elaborator::getNextQuestion(Character * asker, 
        Character * answerer) {
    return CharacterAction(asker, "question", "?", {});
}
CharacterAction Elaborator::answerQuestion(CharacterAction question, Character * asker, 
        Character * answerer) {
    return CharacterAction(answerer, "explaining2", "!", {});
}

PageSketch * Elaborator::elaborateBattle(Report * report) {
    int desiredFrames = ELABORATOR_DESIRED_FRAMES;
    vector<Frame *> frames = {};
    int framesNeeded = desiredFrames - frames.size();
    EventBattle * event = dynamic_cast<EventBattle *>(report->event);

    while (framesNeeded > 0) {
        Frame * frame = nullptr;
        if (framesNeeded == 1) {
            string dialogue = "***";
            if (event->won) {
                dialogue = "We won the battle yay";
            } else {
                dialogue = "We lost much supply in this raid oh no";
            }
            frame = t_1char(CharacterAction(event->participants[0], "stand", dialogue, {}));
        } else {
            frame = t_1char(CharacterAction(rng::randElement(event->participants), "strike", "", {}));
        }
        frames.push_back(frame);
        framesNeeded = desiredFrames - frames.size();
    }

    return new PageSketch(frames);
}

Frame * Elaborator::t_facing(CharacterAction left, CharacterAction right) {
    /**
     * Creates a frame with two characters facing each other.
     * This resets the characters' positions.
     */
    left.position = CharacterActionPosition(.2, .5, .5, DIRECTION_RIGHT);
    right.position = CharacterActionPosition(.8, .5, .5, DIRECTION_LEFT);
    return new Frame({left, right});
}

Frame * Elaborator::t_1char(CharacterAction character, bool direction) {
    /**
     * A frame showing 1 character in the middle
     */
    character.position = CharacterActionPosition(.5, .5, .8, direction);
    return new Frame({character});
}