#include "CPU.h"

#include <stdexcept>

CPU::CPU(u8* mem, u16 memSize)
{
	if (memSize < 0xFFFF) throw std::runtime_error("Invalid memory size.");
	Memory = mem;
	MemorySize = memSize;
	PowerUp();
}

void CPU::PowerUp()
{
	RegX = 0;
	RegA = 0;
	RegY = 0;
	SP = STACK_START_LOW;
	PC = 0;
	Flags = 0x34;
	debugRunning = false;
	Reset();
}

void CPU::SwapMemory(u8* mem, u16 memSize)
{
	if (Memory != mem) delete[] Memory;
	Memory = mem;
	MemorySize = memSize;
}

CPU::~CPU()
{
	if (Memory != nullptr)
		delete[] Memory;
}

void CPU::IRQ()
{
	if (get_ind() == 0)
		Interupt(IRQ_VECTOR);
}

void CPU::NMI()
{
	Interupt(NMI_VECTOR);
}

void CPU::Reset()
{
	Interupt(RESET_VECTOR);
}
