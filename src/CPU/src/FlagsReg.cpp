#include "FlagsReg.h"

void FlagsReg::setFlagsBit(u8 index, bool val)
{
    if (val == 0)
        reg &= ~(1 << index);
    else
        reg |= 1 << index;
}

void FlagsReg::testCarry(u16 res)
{
    setFlagCarry(res > 255);
}

void FlagsReg::testNegative(u8 arg)
{
    setFlagNegative((i8)arg < 0);
}

void FlagsReg::testOverflow(u8 res, u8 a, u8 b)
{
    setFlagOverflow(((b ^ res) & (a ^ res) & 0x80) >> 7);
}

void FlagsReg::testZero(u8 arg)
{
    setFlagZero(arg == 0);
}

u8 FlagsReg::getFlagsBit(u8 index) { return (reg >> index) & 1; }

void FlagsReg::setFlagCarry(bool val) { setFlagsBit(0, val); }

u8 FlagsReg::getFlagCarry() { return getFlagsBit(0); }

void FlagsReg::setFlagZero(bool val) { setFlagsBit(1, val); }

u8 FlagsReg::getFlagZero() { return getFlagsBit(1); }

// Interrupt Disable
void FlagsReg::setFlagInd(bool val) { setFlagsBit(2, val); }

u8 FlagsReg::getFlagInd() { return getFlagsBit(2); }

void FlagsReg::setFlagDecimal(bool val) { setFlagsBit(3, val); }

u8 FlagsReg::getFlagDecimal() { return getFlagsBit(3); }

void FlagsReg::setFlagBreak(bool val) { setFlagsBit(4, val); }

u8 FlagsReg::getFlagBreak() { return getFlagsBit(4); }

void FlagsReg::setFlagOverflow(bool val) { setFlagsBit(6, val); }

u8 FlagsReg::getFlagOverflow() { return getFlagsBit(6); }

void FlagsReg::setFlagNegative(bool val) { setFlagsBit(7, val); }

u8 FlagsReg::getFlagNegative() { return getFlagsBit(7); }

u8 FlagsReg::getVal() { return reg; }

void FlagsReg::reset() { reg = DEFAULT_VAL; }

void FlagsReg::setVal(u8 val) { reg = val; }