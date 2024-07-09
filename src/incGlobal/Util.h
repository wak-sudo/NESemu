#pragma once

#include <string>

typedef unsigned char u8;
typedef unsigned short u16;
typedef char i8;
typedef short i16;
typedef unsigned long u64;


namespace Util
{
    u16 mergeBytes(u8 low, u8 high);
    enum NumericalSystems
    {
        DEC,
        HEX,
        BIN
    };
    std::string toSystem(u64 val, NumericalSystems targetSys);
}

#define KB 1024