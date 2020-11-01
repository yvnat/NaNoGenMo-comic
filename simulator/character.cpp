// character.cpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
// 

#include "character.hpp"

#include "misc.hpp"

#include <fstream>

using namespace std;

Character::Character() {
    this->relationships = {};
    
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

Character::~Character() {
    for (int i = relationships.size()-1; i >= 0; --i) {
        delete relationships[i];
    }
    PRINT("Destroyed character " + name);
}