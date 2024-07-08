#include "CPU.h"

void CPU::transferGeneric(u8 *argFrom, u8 *argTo)
{
	*argTo = *argFrom;
	Flags.testNegative(*argTo);
	Flags.testZero(*argTo);
}

void CPU::op_tax() { transferGeneric(&RegA, &RegX); }

void CPU::op_tay() { transferGeneric(&RegA, &RegY); }

void CPU::op_txa() { transferGeneric(&RegX, &RegA); }

void CPU::op_tya() { transferGeneric(&RegY, &RegA); }

void CPU::op_tsx()
{
	u8 tempSPval = SP->getVal();
	transferGeneric(&tempSPval, &RegX);
}

void CPU::op_txs() { SP->setVal(RegX); }
