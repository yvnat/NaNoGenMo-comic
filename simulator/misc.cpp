// misc.cpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
// 

#include "misc.hpp"

namespace rng {
    std::random_device _rand;
	std::default_random_engine _eng{static_cast<long unsigned int>(time(0))};
}

bool rng::randBool(float p) {
    /**
     * Return true with probability of p
     * where p is in range [0, 1]
     */
    std::uniform_real_distribution<float> d(0.0, 1.0);
    return d(_eng) < p;
}
int rng::randInt(int min, int max) {
    /**
     * Return a random int in range [min, max)
     */
    std::uniform_int_distribution<> d(min, max);
    return d(_eng);
}
float rng::randFloat(float min, float max) {
    /**
     * Return a random float in range [min, max)
     */
    std::uniform_real_distribution<> d(min, max);
    return d(_eng);
}
std::string rng::randomGenericName(int length) {
    /**
     * Quickly generates a random name
     */
    std::string name = "";
    std::string vowels[] = {"a", "e", "o", "u", "i"};
    std::string consonents[] = {"b", "c", "d", "e", "f", "g", "h", "j", "k", "l", "m", "n", "p", "q", "r", "s", "t", "v", "w", "x", "y", "z"};
    for (int i = 0; i < length; ++i) {
        if (i%2 == 0) {
            name += vowels[randInt(0, sizeof(vowels) / sizeof(vowels[0]))];
        } else {
            name += consonents[randInt(0, sizeof(vowels) / sizeof(vowels[0]))];
        }
    }
    return name;
}