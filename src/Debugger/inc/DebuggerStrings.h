#pragma once

#include "Debugger.h"

#include <unordered_map>

class DebuggerStrings : public Debugger
{
    static const std::unordered_map<CPU::ADR_MODE, const char *> adrModeToName;
    static const std::unordered_map<CPU::CPU_STATE, const char *> cpuStateToName;
    static const std::unordered_map<Symbols::OP_SYM, const char *> opcodeSymToName;

    const char *cpuStateToString(CPU::CPU_STATE state) const;
    const char *adrModeToString(CPU::ADR_MODE mode) const;
    const char *opcodeSymToString(Symbols::OP_SYM symbol) const;
    std::string valToStrBase(u8 val) const;
    std::string valToStrBase(u16 val) const;

    void updateDisplayFlags();
    void updateDisplayU8();

protected:
    // Display pairs:
    OCPair<std::string> RegA_display;
    OCPair<std::string> RegX_display;
    OCPair<std::string> RegY_display;
    OCPair<std::string> RegSP_display;
    OCPair<std::string> RegPC_display;
    OCPair<std::string> RegFlags_display;

    OCPair<const char *> CarryFlag_display;
    OCPair<const char *> ZeroFlag_display;
    OCPair<const char *> IndFlag_display;
    OCPair<const char *> DecimalFlag_display;
    OCPair<const char *> BreakFlag_display;
    OCPair<const char *> UnusedFlag_display;
    OCPair<const char *> OverflowFlag_display;
    OCPair<const char *> NegativeFlag_display;

    OCPair<std::string> Argument_display;
    OCPair<std::string> NoOfBytes_display;
    OCPair<std::string> OpcodeNumber_display;
    OCPair<std::string> Cycles_display;
    OCPair<const char *> OpcodeSym_display;
    OCPair<const char *> AdrMode_display;

    OCPair<const char *> CPUstate_display;

    Util::NumericalSystems numeralSystem = Util::HEX;

    void updateDisplay();
    void update();
public:
    DebuggerStrings(CPU *cpuObjArg, u8 *memoryArg, u64 memorySizeArg);
    void step();
};