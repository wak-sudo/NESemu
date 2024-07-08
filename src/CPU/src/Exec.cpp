#include "CPU.h"

#include <stdexcept>
#include <string>

void CPU::StartExecuting()
{
	PowerUp();
	PC = Util::mergeBytes(Memory[RESET_VECTOR], Memory[RESET_VECTOR + 1]);
	// Todo: page crossing, branch taking

	u8 opcode;
	std::unordered_map<u8, std::tuple<u8, FunPtr, CPU::ADR_MODE>>::const_iterator opMapIt;
	u8 cycles;
	ADR_MODE mode;
	u8 noOfBytes;

	while (CPUstate != POWER_OFF)
	{
		opcode = Memory[PC];
		opMapIt = OpTable.find(opcode);
		if (opMapIt == OpTable.end())
			throw std::runtime_error("Unknown opcode: " + std::to_string(opcode));
		const auto &opInfo = opMapIt->second;
		cycles = std::get<0>(opInfo);
		FunPtr fun = std::get<1>(opInfo);
		mode = std::get<2>(opInfo);
		noOfBytes = AdrModeToBytes.find(mode)->second; // all modes are inluded so no check, maybe chagne this to a normal array?
		invokeOpcode(fun, noOfBytes, mode);

		// Handles interupts.
		auto it = CpuStateToFun.find(CPUstate);
		if (it != CpuStateToFun.end())
			(it->second).invoke(this, Porv());
	}
}

// Execute an opcode.
void CPU::invokeOpcode(FunPtr fun, u8 noOfBytes, ADR_MODE mode)
{
	u16 val = getBytesAfterPC(noOfBytes - 1);
	PC += noOfBytes; // WE SET PC TO NEXT INS BEFORE ADRESS HANDLING AND EXEC.
	Porv arg = handleAdressing(val, mode);
	fun.invoke(this, arg);
}

void CPU::Interupt(u16 vector)
{
	// See how PC is incremented in handleAdressing.
	SP->pushStack((PC + 1) >> 8);
	SP->pushStack(PC + 1);
	SP->pushStack(Flags.getVal());
	Flags.setFlagInd(1); // should it be done before?
	PC = Util::mergeBytes(Memory[vector], Memory[vector + 1]);
	CPUstate = NORMAL_STATE;
}

// Sometimes this functio needs to return a number, sometime a pointer to addres in memory,
// depending on a addressing mode.
Porv CPU::handleAdressing(u16 val, ADR_MODE mode)
{
	// Note: look how JSR and JMP instructions are implemented.
	Porv result;
	switch (mode)
	{
	case Imp:
		result.val = 0;
		break;
	case Acc:
		result.ptr = &RegA;
		break;
	case Imm:
		result.val = val;
		break;
	case Abs:
		result.ptr = &Memory[val];
		break;
	case XIdxAbs:
		result.ptr = &Memory[val + RegX];
		break;
	case YIdxAbs:
		result.ptr = &Memory[val + RegY];
		break;
	case AbsInd:
		result.ptr = &Memory[Memory[val]];
		break;
	case ZP:
		result.ptr = &Memory[val];
		break;
	case XIdxZP:
		result.ptr = &Memory[(val + RegX) % 256];
		break;
	case YIdxZP:
		result.ptr = &Memory[(val + RegY) % 256];
		break;
	case XIdxZPInd:
	{
		u8 address = val + RegX;
		result.ptr = &Memory[Memory[address] + (Memory[address + 1] << 8)];
		break;
	}
	case ZPIndYIdx:
		result.ptr = &Memory[Memory[val] + (Memory[(u8)(val + 1)] << 8) + RegY];
		break;
	case Rel:
		// The second byte of-the instruction
		// becomes the operand which is an �Offset"
		// added to the contents of the lower eight bits
		// of the program counter when the counter
		// is set at the next instruction.

		result.val = (i8)val + PC;
		break;
	default:
		throw std::invalid_argument("Unimplemented branch in handleAdressing");
		break;
	}
	return result;
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