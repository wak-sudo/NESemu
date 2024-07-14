#pragma once

#include "CPU.h"
#include "OCPair.h"

class Debugger
{
    void updateFlags();
    void updateRegistersAndCPUstate();
    void updateOpcodeFields();
    u16 getArgument(u8 noOfBytes);
    void consValFields();
protected:
    void updateVals();

    CPU *cpuObj;
    u8 *memory;
    u64 memorySize;

    // Saved values:
    OCPair<u8> RegA;
    OCPair<u8> RegX;
    OCPair<u8> RegY;
    OCPair<u8> RegSP;
    OCPair<u16> RegPC;
    OCPair<FlagsReg> RegFlags;

    OCPair<bool> CarryFlag;
    OCPair<bool> ZeroFlag;
    OCPair<bool> IndFlag;
    OCPair<bool> DecimalFlag;
    OCPair<bool> BreakFlag;
    OCPair<bool> UnusedFlag;
    OCPair<bool> OverflowFlag;
    OCPair<bool> NegativeFlag;

    OCPair<Symbols::OP_SYM> OpcodeSym;
    OCPair<u8> NoOfBytes;
    OCPair<u8> OpcodeNumber;
    OCPair<u8> Cycles;
    OCPair<CPU::ADR_MODE> AdrMode;
    OCPair<u16> Argument;

    OCPair<CPU::CPU_STATE> CPUstate;

public:
    Debugger(CPU *cpuObjArg, u8 *memoryArg, u64 memorySizeArg);
    void step();
};