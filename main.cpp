#include <iostream>
#include "Core/Headers/GameFramework.h"

int main()
{
    system("chcp 65001");

    GameFramework game{};
    game.StartGame();

    return 0;
}