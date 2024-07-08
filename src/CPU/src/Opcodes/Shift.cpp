#include "CPU.h"

void CPU::op_asl(u8* arg)
{
	Flags.setFlagCarry( (*arg & 0x80) >> 7 );
	*arg <<= 1;
	Flags.testNegative(*arg);
	Flags.testZero(*arg);
}

void CPU::op_lsr(u8* arg)
{
	Flags.setFlagCarry(*arg & 1);
	*arg >>= 1;
	Flags.setFlagNegative(0);
	Flags.testZero(*arg);
}

void CPU::op_rol(u8* arg)
{
	u8 cbit = *arg & 0x80;
	*arg <<= 1;
	*arg |= cbit;
	Flags.setFlagCarry(cbit);
	Flags.testNegative(*arg);
	Flags.testZero(*arg);
}

void CPU::op_ror(u8* arg)
{
	u8 cbit = *arg & 1;
	*arg >>= 1;
	*arg |= (cbit << 7);
	Flags.setFlagCarry(cbit);
	Flags.testNegative(*arg);
	Flags.testZero(*arg);
}