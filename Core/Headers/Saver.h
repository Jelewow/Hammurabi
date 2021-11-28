#include <fstream>
#include <filesystem>

#include "../Headers/PlayerStats.h"
#include "RoundInfo.h"

class Saver
{
private:
    const std::string filename = "SavedGame.bin";

public:
    bool IsFileExist();

    void Save(RoundInfo &roundInfo);

    void TryLoad(RoundInfo &roundInfo);
};

