#include <iostream>
#include <algorithm>
#include "PlayerStats.h"
#include "Core.h"
#include "RoundInfo.h"
#include "Saver.h"

class GameFramework
{
private:
    const int kMaxCostPerAcr = 26;
    const int kMinCostPerAcr = 17;
    const int kMaxRounds = 10;
    const int kMaxProcessAcres = 10;
    const int kMaxWheatPerAcr = 6;
    const int kMinWheatPerAcr = 1;
    const int kStartPopulation = 100;
    const int kStartAcres = 100;
    const double kStartWheat = 2800;

    std::vector<double> dead_percentage;
    double P; //среднегодовой процент мертвых от голода
    double L; //колво акров на 1 жителя

    PlayerStats stats;
    RoundInfo roundInfo;
    Core core;
    Saver saver;

    void ShowStartInfo() const;

    void SeparateText() const;

    void GameLoop(bool isContinueGame);

    void GameOver();

    void ShowRoundInfo(RoundInfo &roundInfo);

    void WinGame();

    void Retry();

    bool TryExitGame();

    int GetRandomValue(int minValue, int maxValue);

public:
    void StartGame();
};