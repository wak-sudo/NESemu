#include "CPU.h"

void CPU::decGeneric(u8* arg)
{
	*arg -= 1;
	checkNegative(*arg);
	checkZero(*arg);
}

void CPU::incGeneric(u8* arg)
{
	*arg += 1;
	checkNegative(*arg);
	checkZero(*arg);
}

void CPU::op_dec(u8* arg) { decGeneric(arg); }

void CPU::op_dex() { decGeneric(&RegX); }

void CPU::op_dey() { decGeneric(&RegY); }

void CPU::op_inc(u8* arg) { incGeneric(arg); }

void CPU::op_inx() { incGeneric(&RegX); }

void CPU::op_iny() { incGeneric(&RegY); }