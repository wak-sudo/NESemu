#include "DebuggerStrings.h"

const std::unordered_map<CPU::ADR_MODE, const char *> DebuggerStrings::adrModeToName = {
    {CPU::Imp, "Implied"},
    {CPU::Acc, "Accumulator"},
    {CPU::Imm, "Immediate"},
    {CPU::Abs, "Absolute"},
    {CPU::XIdxAbs, "X-Indexed Absolute"},
    {CPU::YIdxAbs, "Y-Indexed Absolute"},
    {CPU::AbsInd, "Absolute Indirect"},
    {CPU::ZP, "Zero Page"},
    {CPU::XIdxZP, "X-Indexed Zero Page"},
    {CPU::YIdxZP, "Y-Indexed Zero Page"},
    {CPU::XIdxZPInd, "X-Indexed Zero Page Indirect"},
    {CPU::ZPIndYIdx, "Zero Page Indirect Y-Indexed"},
    {CPU::Rel, "Relative"},
};

const std::unordered_map<CPU::CPU_STATE, const char *> DebuggerStrings::cpuStateToName = {
    {CPU::IRQ_SIG, "IRQ_SIG"},
    {CPU::NMI_SIG, "NMI_SIG"},
    {CPU::RESET_SIG, "RESET_SIG"},
    {CPU::NORMAL_STATE, "NORMAL_STATE"},
    {CPU::POWER_OFF, "POWER_OFF"},
};

using namespace Symbols;

const std::unordered_map<Symbols::OP_SYM, const char *> DebuggerStrings::opcodeSymToName = {
    {AND, "AND"},
    {BIT, "BIT"},
    {EOR, "EOR"},
    {ORA, "ORA"},
    // Arith:
    {ADC, "ADC"},
    {CMP, "CMP"},
    {CPX, "CPX"},
    {CPY, "CPY"},
    {SBC, "SBC"},

    // Shift:
    {ASL, "ASL"},
    {LSR, "LSR"},
    {ROL, "ROL"},
    {ROR, "ROR"},

    // Bra:
    {BCC, "BCC"},
    {BCS, "BCS"},
    {BEQ, "BEQ"},
    {BMI, "BMI"},
    {BNE, "BNE"},
    {BPL, "BPL"},
    {BVC, "BVC"},
    {BVS, "BVS"},

    // Ctrl:
    {BRK, "BRK"},
    {JMP, "JMP"},
    {JSR, "JSR"},
    {RTI, "RTI"},
    {RTS, "RTS"},

    // Flags:
    {CLC, "CLC"},
    {CLD, "CLD"},
    {CLI, "CLI"},
    {CLV, "CLV"},
    {SEC, "SEC"},
    {SED, "SED"},
    {SEI, "SEI"},

    // Inc:
    {DEC, "DEC"},
    {DEX, "DEX"},
    {DEY, "DEY"},
    {INC, "INC"},
    {INX, "INX"},
    {INY, "INY"},

    // Load:
    {LDA, "LDA"},
    {LDX, "LDX"},
    {LDY, "LDY"},
    {STA, "STA"},
    {STX, "STX"},
    {STY, "STY"},

    // Stack:
    {PHA, "PHA"},
    {PHP, "PHP"},
    {PLA, "PLA"},
    {PLP, "PLP"},

    // Trans:
    {TAX, "TAX"},
    {TAY, "TAY"},
    {TSX, "TSX"},
    {TXA, "TXA"},
    {TXS, "TXS"},
    {TYA, "TYA"},

    // Nop:
    {NOP, "NOP"},

    // Undocumented
    {JAM, "JAM"},

    // Rest"
    {UNK, "UNK"},
};