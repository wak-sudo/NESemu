#pragma once

#include <unordered_map>
#include <tuple>
#include <string>

#include "Util.h"

#include "FlagsReg.h"
#include "StackReg.h"
#include "FunPtr.h"
#include "Symbols.h"

class CPU
{
public:
	enum CPU_STATE
	{
		IRQ_SIG,
		NMI_SIG,
		RESET_SIG,
		NORMAL_STATE,
		POWER_OFF
	};

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
	enum ADR_MODE
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

	CPU(u8 *mem, u64 memSize);
	~CPU();
	void PowerUp();
	void ExecutionStep();
	void SwapMemory(u8 *mem, u64 memSize, bool deleteOld = false);

	void IRQ();
	void NMI();
	void RESET();

	// Regs:
	u16 getRegPC() const;
	u8 getRegA() const; // ACC
	u8 getRegX() const;
	u8 getRegY() const;
	u8 getRegSP() const;
	u8 getRegFlagsVal() const;
	FlagsReg getRegFlagsObj() const;
	CPU_STATE getState() const;

	void LoadBinary(std::string filePath, u16 startingPoint);

	u8 getCurrentIns() const; // this may only be needed for debug.

	std::tuple<Symbols::OP_SYM, u8, CPU::ADR_MODE, u8> getOpcodeInfo(u8 opcode) const;

private:
	const u16 IRQ_VECTOR = 0xFFFE;
	const u16 RESET_VECTOR = 0xFFFC;
	const u16 NMI_VECTOR = 0xFFFA;

	const double COL_SUB_FREQ = 3.579545;
	const double MASTER_CLOCK_FREQ = 21.477272;
	const double CLOCK_DIVISOR = 12;
	const double CPUCLOCK_FREQ = 1.789773;

	static const std::unordered_map<u8, std::tuple<u8, FunPtr, ADR_MODE>> OpTable;
	static const std::unordered_map<ADR_MODE, u8> AdrModeToBytes;
	static const std::unordered_map<CPU_STATE, FunPtr> CpuStateToFun;

	// Debug related:
	struct FunPtrHasher
	{
		size_t operator()(const FunPtr &p) const;
	};
	static const std::unordered_map<FunPtr, Symbols::OP_SYM, FunPtrHasher> opcodeFunToSym;
	// End of Debug related:

	u8 *Memory; // Is is the best way?
	u64 MemorySize;
	u8 RegA, RegX, RegY;
	FlagsReg Flags;
	StackReg *SP;
	u16 PC;

	CPU_STATE CPUstate;

	void Interupt(u16 vector);
	Porv handleAdressing(u16 val, ADR_MODE mode);
	void executeNextOpcode(FunPtr fun, u8 noOfBytes, ADR_MODE mode);

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
