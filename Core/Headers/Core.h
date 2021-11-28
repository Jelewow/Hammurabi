#include <iostream>
#include <string>
#include <random>
#include "InputInfo.h"
#include "../Headers/PlayerStats.h"
#include "ValidateInfo.h"

class Core
{
private:
    bool TryValidateValue(int inputValue, double currentValue);

    void ShowMistake(PlayerStats &stats);

public:
    const std::string outputInfo[4] = {"Сколько акров земли повелеваешь купить? : ",
                                       "Сколько акров земли повелеваешь продать? : ",
                                       "Сколько бушелей пшеницы повелеваешь съесть? : ",
                                       "Сколько акров земли повелеваешь засеять? : "};

    InputInfo ReadInput(ValidateInfo &validateInfo, PlayerStats &stats);
};