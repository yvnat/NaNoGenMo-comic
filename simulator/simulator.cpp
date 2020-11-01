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

Report * Simulator::simulateTurn() {
    //temp
    //set random action
    vector<ActionType> actions = {ActionType::CAMPING, ActionType::MARCHING};
    currentAction = rng::randElement(actions);
    if (currentAction == ActionType::MARCHING && rng::randBool(0.5)) {
        // if marching, 50% chance to switch terrain
        vector<TerrainType> terrains = {TerrainType::FIELDS, TerrainType::FORESTS, TerrainType::HILLS};
        currentTerrain = rng::randElement(terrains);
    }
    Event * thisTurnsEvent = getNextEvent();
    vector<Outcome *> outcomes = resolveEvent(thisTurnsEvent);
    Report * report = generateReport(currentTerrain, currentAction, thisTurnsEvent, outcomes);
    history.push_back(report);
    return report;
}

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
            outcomes.push_back(new Outcome(OutcomeType::SUPPLIES_CHANGE));
            outcomes.push_back(new Outcome(OutcomeType::MORALE_CHANGE));
        } else {
            outcomes.push_back(new Outcome(OutcomeType::MORALE_CHANGE));
        }
    }
    if (event->type == EventType::TALK) {
        outcomes.push_back(new Outcome(OutcomeType::RELATIONSHIP_CHANGE));
    }
    return outcomes;
}

Report * Simulator::generateReport(TerrainType terrain, ActionType action, 
                         Event * event, std::vector<Outcome *> outcomes) {
    return new Report(terrain, action, event, outcomes);
}