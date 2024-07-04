#include "CPU.h"

void CPU::op_nop() {}

void CPU::op_jam()
{
	debugRunning = false;
}