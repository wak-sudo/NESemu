#include "CPU.h"

void CPU::op_brk()
{
	CPUstate = IRQ_SIG;
}

void CPU::op_jmp(u8* arg)
{
	u16 address = (u16)(arg - Memory);
	PC = address;
}

void CPU::op_jsr(u8* arg)
{
	// See how PC is incremented in handleAdressing. 
	SP->pushStack((PC - 1) >> 8);
	SP->pushStack(PC - 1);
	u16 address = (u16)(arg - Memory);
	PC = address;
}

void CPU::op_rti()
{
	Flags.setVal(SP->popStack());
	PC = Util::mergeBytes(SP->popStack(), SP->popStack());
}

void CPU::op_rts()
{
	PC = Util::mergeBytes(SP->popStack(), SP->popStack()) + 1;
}

