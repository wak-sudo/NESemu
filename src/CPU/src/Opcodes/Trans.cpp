#include "CPU.h"

void CPU::transferGeneric(u8* argFrom, u8* argTo)
{
	*argTo = *argFrom;
	checkNegative(*argTo);
	checkZero(*argTo);
}

void CPU::op_tax() { transferGeneric(&RegA, &RegX); }

void CPU::op_tay() { transferGeneric(&RegA, &RegY); }

void CPU::op_txa() { transferGeneric(&RegX, &RegA); }

void CPU::op_tya() { transferGeneric(&RegY, &RegA); }

void CPU::op_tsx() { transferGeneric(&SP, &RegX); }

void CPU::op_txs() { SP = RegX; }

