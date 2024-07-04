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
	pushStack((PC - 1) >> 8);
	pushStack(PC - 1);
	u16 address = (u16)(arg - Memory);
	PC = address;
}

void CPU::op_rti()
{
	Flags = popStack();
	PC = mergeBytes(popStack(), popStack());
}

void CPU::op_rts()
{
	PC = mergeBytes(popStack(), popStack()) + 1;
}

