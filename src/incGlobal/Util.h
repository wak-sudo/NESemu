#pragma once

#include <string>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned short u32;
typedef unsigned long u64;
typedef char i8;
typedef short i16;

namespace Util
{
    u16 mergeBytes(u8 low, u8 high);
    enum NumericalSystems
    {
        DEC,
        HEX,
        BIN
    };
    std::string toSystemGeneric(u64 val, NumericalSystems targetSys);
    std::string toSystem(u8 val, NumericalSystems targetSys);
    std::string toSystem(u16 val, NumericalSystems targetSys);

    void debug(std::string str);

    u16 getBytesFromMemAfterIdx(u8* mem, u16 idx, u16 numberOfBytes);
}

#define KB 1024