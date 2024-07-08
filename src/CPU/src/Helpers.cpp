#include "CPU.h"

#include <stdexcept>

CPU::CPU_STATE CPU::getCPUstate() { return CPUstate; }

// This functions returns number of bytes after the program counter position in little endian.
u16 CPU::getBytesAfterPC(u16 numberof)
{
	if(numberof > 2) throw std::runtime_error("u16 CPU::getBytes(u16 numberof)");
	// We assume that all opcodes are 1 byte!
	if (numberof == 2) return Util::mergeBytes(Memory[PC + 1], Memory[PC + 2]);
	else if (numberof == 1) return Memory[PC + 1];
	else return 0;
}