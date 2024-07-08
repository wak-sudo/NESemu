#include "CPU.h"

void CPU::op_and(u8 arg)
{
	RegA &= arg;
	Flags.testZero(RegA);
	Flags.testNegative(RegA);
}

void CPU::op_bit(u8 arg)
{
	u8 res = RegA & arg;
	Flags.testNegative(arg);
	Flags.setFlagOverflow((arg & 0x40) >> 6);
	Flags.testZero(res);
}

void CPU::op_eor(u8 arg)
{
	RegA ^= arg;
	Flags.testZero(RegA);
	Flags.testNegative(RegA);
}

void CPU::op_ora(u8 arg)
{
	RegA |= arg;
	Flags.testZero(RegA);
	Flags.testNegative(RegA);
}