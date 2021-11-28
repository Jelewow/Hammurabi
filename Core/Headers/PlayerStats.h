#pragma once

#include <fstream>
#include <iostream>
#include "../Headers/PlayerStats.h"

struct PlayerStats
{
    int population;
    double wheat;
    int acres;

    friend std::ostream& operator << (std::ostream& output, PlayerStats& stats);
    friend std::istream& operator >> (std::istream& input, PlayerStats& stats);
};