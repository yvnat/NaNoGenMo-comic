// simulator.cpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
// 

#include "simulator.hpp"
#include "misc.hpp"

using namespace std;

Simulator::Simulator() {
    //temp
    this->currentTerrain = TerrainType::FIELDS;
    this->currentAction = ActionType::MARCHING;
    this->characters = {};
    for (int i = 0; i < 4; ++i) {
        characters.push_back(new Character());
    }
    this->history = {};
    this->morale = 4;
    this->supplies = 5;
    PRINT("Constructed simulator");
}

Simulator::~Simulator() {
    for (int i = characters.size()-1; i >= 0 ; --i) {
        delete characters[i];
    }
    for (int i = history.size()-1; i >= 0 ; --i) {
        delete history[i];
    }
    PRINT("Destroyed simulator");
}

//#############################################################################//

Character * Simulator::getCommander() {
    /**
     * Returns the character with the role of commander
     */
    if (characters.size() == 0) {
        PRINT("characters.size() == 0");
    }
    return characters[0];
}

//#############################################################################//

Report * Simulator::simulateTurn() {
    //temp
    //set random action
    PRINT("Simulating turn");
    vector<ActionType> actions = {ActionType::CAMPING, ActionType::MARCHING};
    currentAction = rng::randElement(actions);
    if (currentAction == ActionType::MARCHING && rng::randBool(0.5)) {
        // if marching, 50% chance to switch terrain
        vector<TerrainType> terrains = {TerrainType::FIELDS, TerrainType::FORESTS, TerrainType::HILLS};
        currentTerrain = rng::randElement(terrains);
    }
    Event * thisTurnsEvent = getNextEvent();
    vector<Outcome *> outcomes = resolveEvent(thisTurnsEvent);
    enactOutcomes(outcomes);
    Report * report = generateReport(currentTerrain, currentAction, thisTurnsEvent, outcomes);
    history.push_back(report);
    PRINT("Simulated turn");
    return report;
}

//#############################################################################//

Event * Simulator::getNextEvent() {
    /**
     * Picks event at random
     * Temporary implementation
     */
    vector<EventType> options;
    options = {EventType::ATTACKED, EventType::TALK};
    EventType chosenType = rng::randElement<EventType>(options);
    return new Event(chosenType);
}

vector<Outcome *> Simulator::resolveEvent(Event * event) {
    /**
     * Temporary implementation
     */
    vector<Outcome *> outcomes = {};
    if (event->type == EventType::ATTACKED) {
        if (rng::randBool(0.5)) {
            outcomes.push_back(new Outcome_Supplies(-1));
            outcomes.push_back(new Outcome_Morale(-1));
            if (characters.size() > 1) {
                Character * unhappySoldier = rng::randElement(characters);
                while (unhappySoldier == getCommander()) {
                    unhappySoldier = rng::randElement(characters);
                }
                outcomes.push_back(new Outcome_Relationship(unhappySoldier->getRelationship(getCommander()), Justified<int>(-30, "bad commander")));
            }
        } else {
            outcomes.push_back(new Outcome_Morale(+1));
            if (characters.size() > 1) {
                Character * happySoldier = rng::randElement(characters);
                while (happySoldier == getCommander()) {
                    happySoldier = rng::randElement(characters);
                }
                outcomes.push_back(new Outcome_Relationship(happySoldier->getRelationship(getCommander()), Justified<int>(10, "good commander")));
            }
        }
    }
    if (event->type == EventType::TALK) {
        if (characters.size() == 0) {
            //this deserves special treatment
            return outcomes;
        }
        Character * talker1 = rng::randElement(characters);
        Character * talker2 = talker1;
        while (talker2 == talker1) {
            talker2 = rng::randElement(characters);
        }
        outcomes.push_back(new Outcome_Relationship(talker1->getRelationship(talker2), Justified<int>(10, "good chat")));
        outcomes.push_back(new Outcome_Relationship(talker2->getRelationship(talker1), Justified<int>(10, "good chat")));
    }
    return outcomes;
}

void Simulator::enactOutcomes(vector<Outcome *> outcomes) {
    /**
     * enact the effects described in outcomes on the simulation
     */
    for (int i = 0; i < outcomes.size(); ++i) {
        Outcome * outcome = outcomes[i];
        switch (outcome->type) {
            case (OutcomeType::MORALE_CHANGE): {
                //change in morale
                Outcome_Morale * cast = dynamic_cast<Outcome_Morale *>(outcome);
                morale += cast->change;
                break;
            };
            case (OutcomeType::RELATIONSHIP_CHANGE): {
                //change in relationship
                Outcome_Relationship * cast = 
                        dynamic_cast<Outcome_Relationship *>(outcome);
                cast->affectedRelationship->addOpinion(cast->newOpinion);
                break;
            };
            case (OutcomeType::SUPPLIES_CHANGE): {
                //change in supplies
                Outcome_Supplies * cast = 
                        dynamic_cast<Outcome_Supplies *>(outcome);
                supplies += cast->change;
                break;
            };
        }
    }
}

Report * Simulator::generateReport(TerrainType terrain, ActionType action, 
                         Event * event, std::vector<Outcome *> outcomes) {
    return new Report(terrain, action, event, outcomes);
}