#pragma once

#include <fstream>
#include <iostream>
#include "PlayerStats.h"

struct RoundInfo
{
    int current_round;
    int dead_people;
    int new_people;
    bool was_plague;
    int bushels_picked;
    int bushels_per_acre;
    int dead_bushels;
    int town_acres;
    int cost_per_acre;
    PlayerStats playerStats;

    friend std::ostream& operator << (std::ostream& output, RoundInfo& roundInfo);
    friend std::istream& operator >> (std::istream& input, RoundInfo& roundInfo);
};