#include "CPU.h"

// Decimal mode is not taken into account.

void CPU::cmpGeneric(u8 reg, u8 arg)
{
	u8 res = reg - arg;
	Flags.testZero(res);
	Flags.testNegative(res);
	Flags.setFlagCarry(arg <= reg);
}

void CPU::op_cmp(u8 arg) { cmpGeneric(RegA, arg); }

void CPU::op_cpx(u8 arg) { cmpGeneric(RegX, arg); }

void CPU::op_cpy(u8 arg) { cmpGeneric(RegY, arg); }

void CPU::op_adc(u8 arg)
{
	u16 res = RegA + arg + Flags.getFlagCarry();
	Flags.testOverflow((u8)res, RegA, arg);
	Flags.testCarry(res);
	Flags.testNegative((u8)res);
	Flags.testZero((u8)res);
	RegA = (u8)res;
}

void CPU::op_sbc(u8 arg)
{
	u16 res = RegA - arg - ~Flags.getFlagCarry();
	Flags.setFlagCarry(res >= 0);
	Flags.testOverflow((u8)res, RegA, arg);
	Flags.testNegative((u8)res);
	Flags.testZero((u8)res);
	RegA = (u8)res;
}
