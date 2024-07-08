#include "CPU.h"

#include <stdexcept>

CPU::CPU(u8* mem, u16 memSize)
{
	SwapMemory(mem, memSize);

	SP = new StackReg(Memory);

	PowerUp();
}

CPU::~CPU()
{
	if (Memory != nullptr)
		delete[] Memory;
	delete SP;
}

void CPU::PowerUp()
{
	RegX = 0;
	RegA = 0;
	RegY = 0;
	SP->reset();
	PC = 0;
	Flags.reset();
	CPUstate = NORMAL_STATE;
	RESET(); // Interupt signal.
}

void CPU::SwapMemory(u8* mem, u16 memSize, bool deleteOld)
{
	if (memSize != 0xFFFF) throw std::runtime_error("CPU::SwapMemory(u8* mem, u16 memSize) - Invalid memory size.");
	if (Memory != mem && deleteOld) delete[] Memory;
	Memory = mem;
	MemorySize = memSize;
}

void CPU::IRQ()
{
	if (Flags.getFlagInd() == 0)
		Interupt(IRQ_VECTOR);
}

void CPU::NMI()
{
	Interupt(NMI_VECTOR);
}

void CPU::RESET()
{
	Interupt(RESET_VECTOR);
}
