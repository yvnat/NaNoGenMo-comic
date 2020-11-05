// elaborator.hpp
// NaNoGenMo 2020 - Hoplites Comic - yvnat
// the script for a page or so of comic

#pragma once

#include "frame.hpp"

#include <vector>
#include <string>

class PageSketch {
    public:
    std::vector<Frame *> frames;
    PageSketch(std::vector<Frame *> frames);
    ~PageSketch();

    std::string toString();
};