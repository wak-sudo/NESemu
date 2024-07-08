#include "CPU.h"

#include <stdexcept>

CPU::CPU(u8 *mem, u16 memSize)
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

void CPU::SwapMemory(u8 *mem, u16 memSize, bool deleteOld)
{
	if (memSize != 0xFFFF)
		throw std::runtime_error("CPU::SwapMemory(u8* mem, u16 memSize) - Invalid memory size.");
	if (Memory != mem && deleteOld)
		delete[] Memory;
	Memory = mem;
	MemorySize = memSize;
}

// This functions returns number of bytes after the program counter position in little endian.
u16 CPU::getBytesAfterPC(u16 numberof)
{
	if (numberof > 2)
		throw std::runtime_error("u16 CPU::getBytes(u16 numberof)");
	// We assume that all opcodes are 1 byte!
	if (numberof == 2)
		return Util::mergeBytes(Memory[PC + 1], Memory[PC + 2]);
	else if (numberof == 1)
		return Memory[PC + 1];
	else
		return 0;
}

CPU::CPU_STATE CPU::getCPUstate() { return CPUstate; }

u16 CPU::getRegPC() { return PC; }

u8 CPU::getRegA() { return RegA; }

u8 CPU::getRegX() { return RegX; }

u8 CPU::getRegY() { return RegY; }

u8 CPU::getRegSP() { return SP->getVal(); }

u8 CPU::getRegFlags() { return Flags.getVal(); }