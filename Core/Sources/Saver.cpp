#include "../Headers/Saver.h"

bool Saver::IsFileExist()
{
    return std::filesystem::exists(filename);
}

void Saver::Save(RoundInfo &roundInfo)
{
    std::ofstream output(filename, std::ios::binary);
    output << roundInfo;
}

void Saver::TryLoad(RoundInfo &roundInfo)
{
    std::ifstream input(filename, std::ios::binary);
    input >> roundInfo;
}