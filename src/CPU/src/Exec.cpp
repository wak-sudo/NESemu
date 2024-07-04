#include "CPU.h"

#include <stdexcept>
#include <string>

void CPU::StartExecuting()
{
	PowerUp();
	debugRunning = true;
	PC = mergeBytes(Memory[RESET_VECTOR], Memory[RESET_VECTOR + 1]);
	// Todo: page crossing, branch taking
	
	u8 opcode;
	std::unordered_map<u8, std::tuple<u8, CPU::FunPtr, CPU::AdrModes>>::const_iterator opMapIt;
	u8 cycles;
	AdrModes mode;
	u8 noOfBytes;

	while (debugRunning)
	{
		opcode = Memory[PC];
		opMapIt = OpTable.find(opcode);
		if (opMapIt == OpTable.end()) throw std::runtime_error("Unknown opcode: " + std::to_string(opcode));
		const auto& opInfo = opMapIt->second;
		cycles = std::get<0>(opInfo);
		FunPtr fun = std::get<1>(opInfo);
		mode = std::get<2>(opInfo);
		noOfBytes = AdrModeToBytes.find(mode)->second; // all modes are inluded so no check, maybe chagne this to a normal array?
		invokeOpcode(fun, noOfBytes, mode);

		// Handles interupts.
		auto it = CpuStateToFun.find(CPUstate);
		if (it != CpuStateToFun.end()) (this->*(it->second))();
	}	
}

void CPU::invokeOpcode(FunPtr fun, u8 noOfBytes, AdrModes mode)
{
	u16 val = getBytes(noOfBytes - 1);
	FunPtrType funType = fun.type;
	PC += noOfBytes; // WE SET PC TO NEXT INS BEFORE ADRESS HANDLING AND EXEC.
	Porv arg = handleAdressing(val, mode, funType);
	switch (funType)
	{
	case VFZ:
		(this->*(fun.zeroArg))();
		break;
	case VFU8:
		(this->*(fun.u8Arg))((u8)arg.val);
		break;
	case VFPU8:
		(this->*(fun.ptru8Arg))(arg.ptr);
		break;
	case VFU16:
		(this->*(fun.u16Arg))((u16)arg.val);
	default:
		throw std::invalid_argument("Unimplemented branch in invokeOpcode.");
		break;
	}
}

CPU::Porv CPU::handleAdressing(u16 val, AdrModes mode, FunPtrType funType)
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
		// becomes the operand which is an “Offset" 
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


void CPU::Interupt(u16 vector)
{
	// See how PC is incremented in handleAdressing. 
	pushStack((PC + 1) >> 8);
	pushStack(PC + 1);
	pushStack(Flags);
	set_ind(1); // should it be done before?
	PC = mergeBytes(Memory[vector], Memory[vector + 1]);
	CPUstate = NORMAL_STATE;
}
