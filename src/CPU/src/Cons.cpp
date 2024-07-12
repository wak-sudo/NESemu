#include "CPU.h"

#include <stdexcept>

CPU::CPU(u8 *mem, u64 memSize)
{
	SwapMemory(mem, memSize);

	SP = new StackReg(Memory);

	PowerUp();
}

CPU::~CPU()
{
	// CPU does not delete memory!
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

void CPU::SwapMemory(u8 *mem, u64 memSize, bool deleteOld)
{
	if (memSize != 0xFFFF)
		throw std::runtime_error("CPU::SwapMemory(u8* mem, u16 memSize) - Invalid memory size.");
	if (Memory != mem && deleteOld)
		delete[] Memory;
	Memory = mem;
	MemorySize = memSize;
}

std::tuple<u8, CPU::ADR_MODE, u8> CPU::getOpcodeInfo(u8 opcode) const
{
	const auto emptyTuple = std::make_tuple(0, Imp, 0);
	auto itOpTable = OpTable.find(opcode);
	if (itOpTable == OpTable.end())
		return emptyTuple;
	const ADR_MODE mode = std::get<2>(itOpTable->second);
	auto itBytes = AdrModeToBytes.find(mode);
	if (itBytes == AdrModeToBytes.end())
		return emptyTuple;
	const u8 cycles = std::get<0>(itOpTable->second);
	const u8 bytes = itBytes->second;
	return std::make_tuple(cycles, mode, bytes);
}

CPU::CPU_STATE CPU::getState() const { return CPUstate; }

u16 CPU::getRegPC() const { return PC; }

u8 CPU::getRegA() const { return RegA; }

u8 CPU::getRegX() const { return RegX; }

u8 CPU::getRegY() const { return RegY; }

u8 CPU::getRegSP() const { return SP->getVal(); }

u8 CPU::getRegFlagsVal() const { return Flags.getVal(); }

FlagsReg CPU::getRegFlagsObj() const { return Flags; }

u8 CPU::getCurrentIns() const { return Memory[PC]; }