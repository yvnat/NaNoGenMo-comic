// misc.hpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
// various miscellaneous functions

// #define DEBUG

#pragma once

#include <iostream>
#include <random>
#include <ctime>
#include <string>

namespace rng {
	bool randBool(float p);
	int randInt(int min, int max);
	float randFloat(float min, float max);
	template<typename T> T randElement(std::vector<T> array)  {
        /**
         * Picks a random element from a vector
         */
        return array[randInt(0, array.size() - 1)];
    }
	std::string randomGenericName(int length);
}

#ifdef DEBUG
#define PRINT(x) std::cout <<__FILE__<<":"<<__LINE__<<": "<<x<<"\n"
#else
#define PRINT(x) x
#endif

template<class T> class Justified {
    public:
    T data;
    std::string justification;
    Justified<T>() {};
    Justified<T>(T data, std::string justification) {
        this->data = data;
        this->justification = justification;
    }
};