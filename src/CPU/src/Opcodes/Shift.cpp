#include "CPU.h"

void CPU::op_asl(u8* arg)
{
	set_carry( (*arg & 0x80) >> 7 );
	*arg <<= 1;
	checkNegative(*arg);
	checkZero(*arg);
}

void CPU::op_lsr(u8* arg)
{
	set_carry(*arg & 1);
	*arg >>= 1;
	set_negative(0);
	checkZero(*arg);
}

void CPU::op_rol(u8* arg)
{
	u8 cbit = *arg & 0x80;
	*arg <<= 1;
	*arg |= cbit;
	set_carry(cbit);
	checkNegative(*arg);
	checkZero(*arg);
}

void CPU::op_ror(u8* arg)
{
	u8 cbit = *arg & 1;
	*arg >>= 1;
	*arg |= (cbit << 7);
	set_carry(cbit);
	checkNegative(*arg);
	checkZero(*arg);
}