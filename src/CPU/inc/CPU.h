#pragma once

#include <unordered_map>
#include <tuple>
#include <string>

#include "Global.h"

class CPU
{
public:
	CPU(u8 *mem, u16 memSize);
	~CPU();
	void PowerUp();
	void StartExecuting();
	void SwapMemory(u8 *mem, u16 memSize);
	bool isRunning();
	u8 peek(u16 position);

	void IRQ();
	void NMI();
	void Reset();

	void LoadBinary(std::string filePath, u16 startingPoint);

	const u8 STACK_START_LOW = 0xFF;
	const u8 STACK_START_HIGH = 0x01;
	const u16 IRQ_VECTOR = 0xFFFE;
	const u16 RESET_VECTOR = 0xFFFC;
	const u16 NMI_VECTOR = 0xFFFA;

private:
	using vFunZeroArg = void (CPU::*)();
	using vFunOne8Arg = void (CPU::*)(u8 arg);
	using vFunOne8Ptr = void (CPU::*)(u8 *arg);
	using vFunOne16Arg = void (CPU::*)(u16 arg);

	// Imp - Implied
	// Acc - Accumulator
	// Imm - Immediate
	// Abs - Absolute
	// XIdxAbs - X-Indexed Absolute
	// YIdxAbs - Y-Indexed Absolute
	// AbsInd - Absolute Indirect
	// ZP - Zero Page
	// XIdxZP - X-Indexed Zero Page
	// YIdxZP - Y-Indexed Zero Page
	// XIdxZPInd - X-Indexed Zero Page Indirect
	// ZPIndYIdx - Zero Page Indirect Y-Indexed
	// Rel - Relative
	enum AdrModes
	{
		Imp,
		Acc,
		Imm,
		Abs,
		XIdxAbs,
		YIdxAbs,
		AbsInd,
		ZP,
		XIdxZP,
		YIdxZP,
		XIdxZPInd,
		ZPIndYIdx,
		Rel,
	};

	enum enum_CPUstates
	{
		IRQ_SIG,
		NMI_SIG,
		RESET_SIG,
		NORMAL_STATE
	};

	// VFZ - Void funciton zero par
	// VFU8 - Void function param u8
	// VFPU8 - Void function param u8*
	// VFU16 - Void function param u16
	enum FunPtrType
	{
		VFZ,
		VFU8,
		VFPU8,
		VFU16
	};

	struct FunPtr
	{
		FunPtrType type;
		union
		{
			vFunZeroArg zeroArg;
			vFunOne8Arg u8Arg;
			vFunOne8Ptr ptru8Arg;
			vFunOne16Arg u16Arg;
		};

		FunPtr(vFunZeroArg ptr) : zeroArg(ptr), type(VFZ) {}
		FunPtr(vFunOne8Arg ptr) : u8Arg(ptr), type(VFU8) {}
		FunPtr(vFunOne8Ptr ptr) : ptru8Arg(ptr), type(VFPU8) {}
		FunPtr(vFunOne16Arg ptr) : u16Arg(ptr), type(VFU16) {}
	};

	// Opcode -> <Cycles, Function, AdrMode>
	static const std::unordered_map<u8, std::tuple<u8, FunPtr, AdrModes>> OpTable;
	// AdrModes to instruction bytes. It could be a normal array, but for simplicity the map was chosen.
	static const std::unordered_map<AdrModes, u8> AdrModeToBytes;

	static const std::unordered_map<enum_CPUstates, vFunZeroArg> CpuStateToFun;

	const double COL_SUB_FREQ = 3.579545;
	const double MASTER_CLOCK_FREQ = 21.477272;
	const double CLOCK_DIVISOR = 12;
	const double CPUCLOCK_FREQ = 1.789773;

	u8 RegA, RegX, RegY, Flags, SP;
	u16 PC;

	u8 *Memory; // Is is the best way?
	u16 MemorySize;

	enum_CPUstates CPUstate;

	// Tells whether the CPU is running.
	bool debugRunning;

	void Interupt(u16 vector);

	union Porv
	{ // Pointer or value
		u8 *ptr;
		ul val;
		Porv() : ptr(nullptr) {}
	};

	// Sometimes this functio needs to return a number, sometime a pointer to addres in memory,
	// depending on a addressing mode.
	Porv handleAdressing(u16 val, AdrModes mode, FunPtrType funType);

	// This functions returns number of bytes after the program counter position in little endian.
	u16 getBytes(u16 numberof);

	u16 mergeBytes(u8 low, u8 high);

	// used for getting a full Stack address: 0x0100 + SP
	inline u16 getStackAdr();

	// Execute an opcode.
	void invokeOpcode(FunPtr fun, u8 noOfBytes, AdrModes mode);

	// Help functions.
	void setFlagsBit(u8 index, u8 val);
	u8 getFlagsBit(u8 index);
	void set_carry(u8 val);
	u8 get_carry();
	void set_zero(u8 val);
	u8 get_zero();
	void set_ind(u8 val); // Interrupt Disable
	u8 get_ind();
	void set_decimal(u8 val);
	u8 get_decimal();
	void set_break(u8 val);
	u8 get_break();
	// bit 5 - unused?
	void set_overflow(u8 val);
	u8 get_overflow();
	void set_negative(u8 val);
	u8 get_negative();

	void checkNegative(u8 arg);
	void checkOverflow(u8 res, u8 a, u8 b);
	void checkCarry(u16 res);
	void checkZero(u8 arg);

	u8 popStack();
	void pushStack(u8 arg);

	// Opcodes:

	// Generic functions:
	void branchGeneric(u8 flag, bool test, u16 adr);
	void incGeneric(u8 *arg);
	void decGeneric(u8 *arg);
	void cmpGeneric(u8 reg, u8 arg);
	void loadGeneric(u8 *reg, u8 arg);
	void storeGeneric(u8 reg, u8 *arg);
	void popGeneric(u8 *reg); // different from popStack.
	void transferGeneric(u8 *regFrom, u8 *regTo);

	// Logic:
	void op_and(u8 arg);
	void op_bit(u8 arg);
	void op_eor(u8 arg);
	void op_ora(u8 arg);

	// Arith:
	void op_adc(u8 arg);
	void op_cmp(u8 arg);
	void op_cpx(u8 arg);
	void op_cpy(u8 arg);
	void op_sbc(u8 arg);

	// Shift:
	void op_asl(u8 *arg);
	void op_lsr(u8 *arg);
	void op_rol(u8 *arg);
	void op_ror(u8 *arg);

	// Bra:
	void op_bcc(u16 arg);
	void op_bcs(u16 arg);
	void op_beq(u16 arg);
	void op_bmi(u16 arg);
	void op_bne(u16 arg);
	void op_bpl(u16 arg);
	void op_bvc(u16 arg);
	void op_bvs(u16 arg);

	// Ctrl:
	void op_brk();
	void op_jmp(u8 *arg);
	void op_jsr(u8 *arg);
	void op_rti();
	void op_rts();

	// Flags:
	void op_clc();
	void op_cld();
	void op_cli();
	void op_clv();
	void op_sec();
	void op_sed();
	void op_sei();

	// Inc:
	void op_dec(u8 *arg);
	void op_dex();
	void op_dey();
	void op_inc(u8 *arg);
	void op_inx();
	void op_iny();

	// Load:
	void op_lda(u8 arg);
	void op_ldx(u8 arg);
	void op_ldy(u8 arg);
	void op_sta(u8 *arg);
	void op_stx(u8 *arg);
	void op_sty(u8 *arg);

	// Stack:
	void op_pha();
	void op_php();
	void op_pla();
	void op_plp();

	// Trans:
	void op_tax();
	void op_tay();
	void op_tsx();
	void op_txa();
	void op_txs();
	void op_tya();

	// Nop:
	void op_nop();

	// Undocumented
	void op_jam();
};
