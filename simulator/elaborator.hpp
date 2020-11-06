// elaborator.hpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
// takes a report from the simulator and creates a comic page sketch

#pragma once

#include "report.hpp"
#include "pagesketch.hpp"
#include "frame.hpp"

#include <vector>
#include <string>

class Elaborator {
    public:
    std::vector<Report *> pastReports;   //stores all past reports

    Elaborator();
    ~Elaborator();

    PageSketch * elaborate(Report * report);
    private:
    PageSketch * elaborateTalk(Report * report);
    CharacterAction getNextQuestion(Character * asker, Character * answerer);
    CharacterAction answerQuestion(CharacterAction question, Character * asker, 
            Character * answerer);

    PageSketch * elaborateBattle(Report * report);
};