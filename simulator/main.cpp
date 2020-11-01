// main.cpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
// 

#include "simulator.hpp"

#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
    cout << "main.cpp\n";
    Report r = Report();
    r.test();
    Simulator s = Simulator();
    return 0;
}
