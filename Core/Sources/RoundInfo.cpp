#include "../Headers/RoundInfo.h"

std::ostream &operator<<(std::ostream &output, RoundInfo &roundInfo)
{
    output.write(reinterpret_cast<char*>(&roundInfo), sizeof(roundInfo));
    return output;
}

std::istream &operator>>(std::istream &input, RoundInfo &roundInfo)
{
    input.read(reinterpret_cast<char*>(&roundInfo), sizeof(roundInfo));
    return input;
}