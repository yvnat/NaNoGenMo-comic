// character.cpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
// 

#include "character.hpp"

#include "misc.hpp"

#include <fstream>

using namespace std;

CharacterAppearance::CharacterAppearance(bool isArmed, vector<int> colour) {
    this->isArmed = isArmed;
    this->colour = colour;
}
CharacterAppearance::CharacterAppearance() {
    CharacterAppearance(true, {255, 255, 255});
}
CharacterAppearance::~CharacterAppearance() {
    
}

string CharacterAppearance::serialize() {
    return "["+to_string(isArmed)+", ["
            +to_string(colour[0])+", "
            +to_string(colour[1])+", "
            +to_string(colour[2])+
            +"]]";
}

Character::Character() {
    this->relationships = {};
    this->appearance = CharacterAppearance(true, {rng::randInt(128, 255), rng::randInt(128, 255), rng::randInt(128, 255)});
    
    vector<string> loaded_names = loadNamesFromFile("data/greek_names.txt");
    string chosen_name;
    if (loaded_names.size() > 0) {
        chosen_name = rng::randElement(loaded_names);
    } else {
        chosen_name = rng::randomGenericName(6);
    }
    this->name = chosen_name;

    PRINT("Constructed character " + name);
}

Character::~Character() {
    for (auto const& i : relationships) {
        delete i.second;
    }
    PRINT("Destroyed character " + name);
}

Relationship * Character::getRelationship(Character * character) {
    /**
     * Get relationship, creating one if it doesn't exist
     * returns nullptr for own identity
     */
    if (character == this) {
        return nullptr;
    }
    if (relationships.count(character) == 0) {
        relationships[character] = new Relationship(this, character);
    }
    return relationships[character];
}

vector<string> Character::loadNamesFromFile(string filename) {
    fstream file;
	file.open(filename, ios::in);
    vector<string> names = {};
    string content = "";
	if (not file) {
		cout << "Cannot find file " << filename << "\n";
	}
	else {
		if (file.is_open()){
            while(getline(file, content)) {
                names.push_back(content);
            }
        }
        file.close();   //close the file object.
    }
    return names;
}