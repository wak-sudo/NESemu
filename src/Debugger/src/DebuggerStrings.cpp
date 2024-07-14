#include "DebuggerStrings.h"

#include <stdexcept>

DebuggerStrings::DebuggerStrings(CPU *cpuObjArg, u8 *memoryArg, u64 memorySizeArg) : Debugger(cpuObjArg, memoryArg, memorySizeArg)
{
    updateDisplay();
}

const char *DebuggerStrings::adrModeToString(CPU::ADR_MODE mode) const
{
    const auto itAdrMode = adrModeToName.find(mode);
    if (itAdrMode == adrModeToName.end())
        throw std::runtime_error("Debugger::adrModeToString");
    return itAdrMode->second;
}

const char *DebuggerStrings::opcodeSymToString(Symbols::OP_SYM symbol) const
{
    const auto it = opcodeSymToName.find(symbol);
    if (it == opcodeSymToName.end())
        throw std::runtime_error("Debugger::opcodeSymToString"); // maybe automate this?
    return it->second;
}

const char *DebuggerStrings::cpuStateToString(CPU::CPU_STATE state) const
{
    const auto it = cpuStateToName.find(state);
    if (it == cpuStateToName.end())
        throw std::runtime_error("Debugger::cpuStateToString"); // maybe automate this?
    return it->second;
}

std::string DebuggerStrings::valToStrBase(u64 val) const
{
    return Util::toSystem(val, numeralSystem);
}

void DebuggerStrings::updateDisplay()
{
    updateDisplayU8();
    updateDisplayFlags();

    RegPC_display.current = valToStrBase(RegPC.current);
    RegPC_display.old = valToStrBase(RegPC.old);

    RegFlags_display.current = valToStrBase(RegFlags.current.getVal());
    RegFlags_display.old = valToStrBase(RegFlags.old.getVal());

    OpcodeSym_display.current = opcodeSymToString(OpcodeSym.current);
    OpcodeSym_display.old = opcodeSymToString(OpcodeSym.old);

    AdrMode_display.current = adrModeToString(AdrMode.current);
    AdrMode_display.old = adrModeToString(AdrMode.old);

    Argument_display.current = valToStrBase(Argument.current);
    Argument_display.old = valToStrBase(Argument.old);

    CPUstate_display.current = cpuStateToString(CPUstate.current);
    CPUstate_display.old = cpuStateToString(CPUstate.old);
}

void DebuggerStrings::updateDisplayFlags()
{
    auto helperFlags = [](OCPair<const char *> &target, const OCPair<bool> &src)
    {
        const char *vals[] = {"0", "1"};
        target.current = vals[src.current];
        target.old = vals[src.old];
    };

    helperFlags(CarryFlag_display, CarryFlag);
    helperFlags(ZeroFlag_display, ZeroFlag);
    helperFlags(IndFlag_display, IndFlag);
    helperFlags(DecimalFlag_display, DecimalFlag);
    helperFlags(BreakFlag_display, BreakFlag);
    helperFlags(UnusedFlag_display, UnusedFlag);
    helperFlags(OverflowFlag_display, OverflowFlag);
    helperFlags(NegativeFlag_display, NegativeFlag);
}

void DebuggerStrings::updateDisplayU8()
{
    auto helperU8 = [this](OCPair<std::string> &target, const OCPair<u8> &src)
    {
        target.current = valToStrBase(src.current);
        target.old = valToStrBase(src.old);
    };

    helperU8(RegA_display, RegA);
    helperU8(RegX_display, RegX);
    helperU8(RegY_display, RegY);
    helperU8(RegSP_display, RegSP);
    helperU8(NoOfBytes_display, NoOfBytes);
    helperU8(OpcodeNumber_display, OpcodeNumber);
    helperU8(Cycles_display, Cycles);
}

void DebuggerStrings::step()
{
    update();
}

void DebuggerStrings::update()
{
    updateVals();
    updateDisplay();
}