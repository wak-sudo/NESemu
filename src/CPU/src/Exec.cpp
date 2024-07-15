#include "CPU.h"

#include <stdexcept>
#include <string>

/*void CPU::ExecutionStep()
{
	// Todo: page crossing, branch taking

	if (CPUstate != POWER_OFF)
	{
		u8 opcode = Memory[PC];
		const locIter opMapIt = OpTable.find(opcode);
		if (opMapIt == OpTable.end())
			throw std::runtime_error("Unknown opcode: " + std::to_string(opcode));
		const auto &opInfo = opMapIt->second;
		const u8 cycles = std::get<0>(opInfo);
		const FunPtr fun = std::get<1>(opInfo);
		const ADR_MODE mode = std::get<2>(opInfo);
		const u8 noOfBytes = AdrModeToBytes.find(mode)->second;
		executeNextOpcode(fun, noOfBytes, mode);

		// Handles interupts.
		/*auto it = CpuStateToFun.find(CPUstate);
		if (it != CpuStateToFun.end())
		{
			FunPtr fun = it->second;
		}
		//	().invoke(this, Porv());
	}
}*/

void CPU::fetch()
{
	typedef std::unordered_map<u8, std::tuple<u8, FunPtr, CPU::ADR_MODE>>::const_iterator locIter;

	u8 opcodeNumber = Memory[PC];
	const locIter opMapIt = OpTable.find(opcodeNumber);
	if (opMapIt == OpTable.end())
		throw std::runtime_error("Unknown opcode: " + std::to_string(opcodeNumber));
	const auto &opInfo = opMapIt->second;
	const ADR_MODE mode = std::get<2>(opInfo);
	const u8 noOfBytes = AdrModeToBytes.find(mode)->second;
	const u16 val = Util::getBytesFromMemAfterIdx(Memory, PC, noOfBytes - 1);

	PC += noOfBytes; // WE SET PC TO NEXT INS BEFORE ADRESS HANDLING AND EXEC.

	pendingIns.cyclesReq = std::get<0>(opInfo);
	pendingIns.opcode = std::get<1>(opInfo);
	pendingIns.argument = handleAdressing(val, mode);

	// Handles interupts.
	/*auto it = CpuStateToFun.find(CPUstate);
	if (it != CpuStateToFun.end())
	{
		FunPtr fun = it->second;
	}*/
}

void CPU::executeCycles(u32 cycles)
{
	if (CPUstate == POWER_OFF)
		return;

	while (cycles != 0)
	{
		if (pendingIns.cyclesReq <= 0)
			executeIns();

		if (pendingIns.cyclesReq > cycles)
		{
			pendingIns.cyclesReq -= cycles;
			cycles = 0;
		}
		else
		{
			cycles -= pendingIns.cyclesReq;
			pendingIns.cyclesReq = 0;
		}
	}
}

void CPU::executeIns()
{
	fetch();
	pendingIns.opcode.invoke(this, pendingIns.argument);
}

// Execute an opcode.
/*void CPU::executeNextOpcode(FunPtr fun, u8 noOfBytes, ADR_MODE mode)
{
	u16 val = Util::getBytesFromMemAfterIdx(Memory, PC, noOfBytes - 1);
	PC += noOfBytes; // WE SET PC TO NEXT INS BEFORE ADRESS HANDLING AND EXEC.
	Porv arg = handleAdressing(val, mode);
	fun.invoke(this, arg);
}*/

void CPU::Interupt(u16 vector)
{
	// See how PC is incremented in handleAdressing.
	SP->pushStack((PC + 1) >> 8);
	SP->pushStack(PC + 1);
	SP->pushStack(Flags.getVal());
	Flags.setFlagInd(1); // should it be done before?
	//Util::debug(std::to_string(Memory[vector]));
	//Util::debug(std::to_string(Memory[vector+1]));
	PC = Util::mergeBytes(Memory[vector], Memory[vector + 1]);
	//CPUstate = NORMAL_STATE;
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

void CPU::IRQ_INT()
{
	if (Flags.getFlagInd() == 0)
		Interupt(IRQ_VECTOR);
}

void CPU::NMI_INT()
{
	Interupt(NMI_VECTOR);
}

void CPU::RESET_INT()
{
	Interupt(RESET_VECTOR);
}