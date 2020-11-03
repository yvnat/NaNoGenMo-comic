// elaborator.hpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
// takes a report from the simulator and creates a comic page sketch

#pragma once

#include "report.hpp"
#include "pagesketch.hpp"

#include <vector>

class Elaborator {
    std::vector<Report *> pastReports;   //stores all past reports

    Elaborator();
    ~Elaborator();

    PageSketch * elaborate(Report * report);
};