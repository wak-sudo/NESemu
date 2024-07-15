#include "Util.h"

#include <stdexcept>
#include <fstream>
#include <iostream>

u16 Util::mergeBytes(u8 low, u8 high)
{
    return ((u16)high << 8) + low;
}

std::string Util::toSystemGeneric(u64 val, NumericalSystems targetSys)
{
    const char symTable[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    if (val == 0)
        return "0";

    long base = 2;
    if (targetSys == DEC)
        return std::to_string(val).c_str();
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

std::string Util::toSystem(u8 val, NumericalSystems targetSys)
{
    std::string temp = toSystemGeneric((u64)val, targetSys);
    if (targetSys == NumericalSystems::DEC) return temp;

    long reqNumberOfDigits;
    if (targetSys == NumericalSystems::HEX)
        reqNumberOfDigits = 2;
    else if (targetSys == NumericalSystems::BIN)
        reqNumberOfDigits = 8;

    const u16 missingZeros = reqNumberOfDigits - temp.length();
    for (unsigned i = 0; i < missingZeros; i++)
        temp = "0" + temp;

    if (targetSys == NumericalSystems::HEX)
        temp = "0x" + temp;

    return temp;
}

// change that, code duplication.
std::string Util::toSystem(u16 val, NumericalSystems targetSys)
{
    std::string temp = toSystemGeneric((u64)val, targetSys);
    if (targetSys == NumericalSystems::DEC) return temp;

    long reqNumberOfDigits;
    if (targetSys == NumericalSystems::HEX)
        reqNumberOfDigits = 4;
    else if (targetSys == NumericalSystems::BIN)
        reqNumberOfDigits = 16;

    const u16 missingZeros = reqNumberOfDigits - temp.length();
    for (unsigned i = 0; i < missingZeros; i++)
        temp = "0" + temp;

    if (targetSys == NumericalSystems::HEX)
        temp = "0x" + temp;

    return temp;
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

void Util::debug(std::string str)
{
    std::cout << str << std::endl;
}