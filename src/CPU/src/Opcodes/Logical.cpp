#include "CPU.h"

void CPU::op_and(u8 arg)
{
	RegA &= arg;
	checkZero(RegA);
	checkNegative(RegA);
}

void CPU::op_bit(u8 arg)
{
	u8 res = RegA & arg;
	checkNegative(arg);
	set_overflow((arg & 0x40) >> 6);
	checkZero(res);
}

void CPU::op_eor(u8 arg)
{
	RegA ^= arg;
	checkZero(RegA);
	checkNegative(RegA);
}

void CPU::op_ora(u8 arg)
{
	RegA |= arg;
	checkZero(RegA);
	checkNegative(RegA);
}