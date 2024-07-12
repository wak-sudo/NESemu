#include "Util.h"

#include <stdexcept>

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

u16 Util::getBytesFromMemAfterIdx(u8 *mem, u16 idx, u16 numberOfBytes)
{
    if (numberOfBytes == 0)
        return 0;
    if (numberOfBytes > 2)
        throw std::runtime_error("u16 CPU::getBytes(u16 numberof)");
    if (numberOfBytes == 2)
        return Util::mergeBytes(mem[idx + 1], mem[idx + 2]);
    else
        return mem[idx + 1];
}