#include "CPU.h"

void CPU::popGeneric(u8* reg)
{
	*reg = popStack();
	checkNegative(*reg);
	checkZero(*reg);
}

void CPU::op_pha() { pushStack(RegA); }

void CPU::op_php() { pushStack(Flags); }

void CPU::op_pla() { popGeneric(&RegA); }

void CPU::op_plp() { Flags = popStack(); }


