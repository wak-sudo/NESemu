#include "Util.h"

u16 Util::mergeBytes(u8 low, u8 high)
{
    return ((u16)high << 8) + low;
}

std::string Util::toSystem(u64 val, NumericalSystems targetSys)
{
    const char symTable[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    long base = 2;
    if (targetSys == DEC)
        return std::to_string(val);
    else if (targetSys == BIN)
        base = 2;
    else if (targetSys == HEX)
        base = 16;

    std::string res;
    while (val != 0)
    {
        long rem = val % base;
        val /= base;
        res = symTable[rem] + res;
    }

    return res;
}