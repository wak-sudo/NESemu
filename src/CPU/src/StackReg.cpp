#include "StackReg.h"

u8 StackReg::getVal() const { return reg; }

void StackReg::setVal(u8 val) { reg = val; }

u8 StackReg::popStack()
{
	u8 res = memory[getFullStackAdr()];
	reg++;
	return res;
}

void StackReg::pushStack(u8 val)
{
	reg--;
	memory[getFullStackAdr()] = val;
}


u16 StackReg::getFullStackAdr() const
{
	const u16 stackPage = (u16)STACK_START_HIGH << 8;
	return stackPage + reg;
}

void StackReg::reset()
{
    reg = STACK_START_LOW;
}