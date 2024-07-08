#include "CPU.h"

void CPU::popGeneric(u8* reg)
{
	*reg = SP->popStack();
	Flags.testNegative(*reg);
	Flags.testZero(*reg);
}

void CPU::op_pha() { SP->pushStack(RegA); }

void CPU::op_php() { SP->pushStack(Flags.getVal()); }

void CPU::op_pla() { popGeneric(&RegA); }

void CPU::op_plp() { Flags.setVal(SP->popStack()); }


