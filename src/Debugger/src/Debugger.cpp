#include "Debugger.h"

#include <iostream>

Debugger::Debugger(CPU *cpuObjArg, u8 *memoryArg, u64 memorySizeArg)
{
    cpuObj = cpuObjArg;
    memory = memoryArg;
    memorySize = memorySizeArg;
    consValFields();
    updateVals();
}

void Debugger::step()
{
    updateVals();
}

void Debugger::updateRegistersAndCPUstate()
{
    RegA.update(cpuObj->getRegA());
    RegX.update(cpuObj->getRegX());
    RegY.update(cpuObj->getRegY());
    RegSP.update(cpuObj->getRegSP());
    RegPC.update(cpuObj->getRegPC());
    RegFlags.update(cpuObj->getRegFlagsObj());
    CPUstate.update(cpuObj->getState());
}

void Debugger::updateOpcodeFields()
{
    const u8 currentOpcode = cpuObj->getCurrentIns();
    const auto opcodeInfo = cpuObj->getOpcodeInfo(currentOpcode);
    const Symbols::OP_SYM currentOpSym = std::get<0>(opcodeInfo);
    const u8 currentCycles = std::get<1>(opcodeInfo);
    const CPU::ADR_MODE currentMode = std::get<2>(opcodeInfo);
    const u8 currentBytes = std::get<3>(opcodeInfo);

    OpcodeSym.update(currentOpSym);
    AdrMode.update(currentMode);
    Argument.update(getArgument(currentBytes));
    NoOfBytes.update(currentBytes);
    OpcodeNumber.update(currentOpcode);
    Cycles.update(currentCycles);
}

void Debugger::updateFlags()
{
    const FlagsReg currentFlags = cpuObj->getRegFlagsObj();
    CarryFlag.update(currentFlags.getFlagCarry());
    ZeroFlag.update(currentFlags.getFlagZero());
    IndFlag.update(currentFlags.getFlagInd());
    DecimalFlag.update(currentFlags.getFlagDecimal());
    BreakFlag.update(currentFlags.getFlagBreak());
    UnusedFlag.update(currentFlags.getFlagUnused());
    OverflowFlag.update(currentFlags.getFlagOverflow());
    NegativeFlag.update(currentFlags.getFlagNegative());
}

u16 Debugger::getArgument(u8 noOfBytes)
{
    if (noOfBytes == 0)
        return 0;

    const u16 curPC = cpuObj->getRegPC();
    return Util::getBytesFromMemAfterIdx(memory, curPC, noOfBytes);
}

void Debugger::consValFields()
{
    const OCPair<u8> defaultU8 = OCPair<u8>(0, 0);
    const OCPair<u16> defaultU16 = OCPair<u16>(0, 0);
    const OCPair<bool> defaultFlag = OCPair<bool>(false, false);

    RegA = defaultU8;
    RegX = defaultU8;
    RegY = defaultU8;
    RegSP = defaultU8;
    RegPC = defaultU16;

    CarryFlag = defaultFlag;
    ZeroFlag = defaultFlag;
    IndFlag = defaultFlag;
    DecimalFlag = defaultFlag;
    BreakFlag = defaultFlag;
    UnusedFlag = defaultFlag;
    OverflowFlag = defaultFlag;
    NegativeFlag = defaultFlag;

    NoOfBytes = defaultU8;
    OpcodeNumber = defaultU8;
    Cycles = defaultU8;
    Argument = defaultU16;

    RegFlags = OCPair<FlagsReg>(FlagsReg(), FlagsReg());
    OpcodeSym = OCPair<Symbols::OP_SYM>(Symbols::UNK, Symbols::UNK);
    CPUstate = OCPair<CPU::CPU_STATE>(CPU::POWER_OFF, CPU::POWER_OFF);
    AdrMode = OCPair<CPU::ADR_MODE>(CPU::Imp, CPU::Imp);
}

void Debugger::updateVals()
{
    updateRegistersAndCPUstate();
    updateFlags();
    updateOpcodeFields();
}