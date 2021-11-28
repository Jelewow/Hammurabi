#include "../Headers/PlayerStats.h"


std::ostream &operator<<(std::ostream &output, PlayerStats &stats)
{
    output.write(reinterpret_cast<char*>(&stats), sizeof(stats));
    return output;
}

std::istream &operator>>(std::istream &input, PlayerStats &stats)
{
    input.read(reinterpret_cast<char*>(&stats), sizeof(stats));
    return input;
}
