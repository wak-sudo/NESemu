#include "CPU.h"

void CPU::loadGeneric(u8* reg, u8 arg)
{
	*reg = arg;
	checkZero(*reg);
	checkNegative(*reg);
}

void CPU::storeGeneric(u8 reg, u8* arg)
{
	*arg = reg;
}

void CPU::op_lda(u8 arg) { loadGeneric(&RegA, arg); }

void CPU::op_ldx(u8 arg) { loadGeneric(&RegX, arg); }

void CPU::op_ldy(u8 arg) { loadGeneric(&RegY, arg); }

void CPU::op_sta(u8* arg) { storeGeneric(RegA, arg); }

void CPU::op_stx(u8* arg) { storeGeneric(RegX, arg); }

void CPU::op_sty(u8* arg) { storeGeneric(RegY, arg); }

