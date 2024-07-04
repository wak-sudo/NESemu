#include "CPU.h"

u16 CPU::mergeBytes(u8 low, u8 high)
{
	return ((u16)high << 8) + low;
}

u8 CPU::popStack()
{
	u8 res = Memory[getStackAdr()];
	SP++;
	return res;
}

void CPU::pushStack(u8 val)
{
	SP--;
	Memory[getStackAdr()] = val;
}


u16 CPU::getStackAdr()
{
	const u16 stackPage = (u16)STACK_START_HIGH << 8;
	return stackPage + SP;
}

u8 CPU::peek(u16 pos)
{
	return Memory[pos];
}

bool CPU::isRunning() { return debugRunning; }

u16 CPU::getBytes(u16 numberof)
{
	// We assume that all opcodes are 1 byte!
	if (numberof == 2) return mergeBytes(Memory[PC + 1], Memory[PC + 2]);
	else if (numberof == 1) return Memory[PC + 1];
	else return 0;
}