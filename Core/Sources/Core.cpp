#include "../Headers/Core.h"

InputInfo Core::ReadInput(ValidateInfo &validateInfo, PlayerStats &stats)
{
    std::cout << "Что пожелаешь, повелитель?\n";
    InputInfo inputInfo;
    int last_value;
    for (int i = 0; i < 4;)
    {
        std::cout << outputInfo[i];
        int input;
        std::cin >> input;

        if (!TryValidateValue(input, validateInfo[i]))
        {
            ShowMistake(stats);
        }
        else
        {
            switch (i)
            {
                case 0:
                    stats.acres += input;
                    stats.wheat -= input * validateInfo.cost_per_acr;
                    validateInfo.max_acres_can_sold += input;
                    break;
                case 1:
                    stats.acres -= input;
                    stats.wheat += input * validateInfo.cost_per_acr;
                    validateInfo.max_wheat_can_eat = stats.wheat;
                    break;
                case 2:
                    //откладываем на еду
                    stats.wheat -= input;
                    //смотрим с чем сравнивать
                    last_value = (stats.acres > stats.wheat * 2) ? stats.wheat * 2 : stats.acres;
                    last_value = (last_value > validateInfo.max_acres_can_process) ? validateInfo
                            .max_acres_can_process : last_value;
                    validateInfo.max_acres_can_sow = last_value;
                    break;
                case 3:
                    stats.wheat -= input * 0.5;
                    break;
            }
            inputInfo.Add(i, input);
            ++i;
        }
    }
    return inputInfo;
}

bool Core::TryValidateValue(int inputValue, double currentValue)
{
    return inputValue <= currentValue;
}

void Core::ShowMistake(PlayerStats &stats)
{
    std::cout << "О, повелитель, пощади нас! У нас только " << stats.population
              << " человек, " << stats.wheat << " бушелей пшеницы"
              << " и " << stats.acres << " акров земли!\n";

}