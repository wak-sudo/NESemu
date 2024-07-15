#include "CPU.h"

// AdrModes to instruction bytes. It could be a normal array, but for simplicity the map was chosen.
const std::unordered_map<CPU::ADR_MODE, u8> CPU::AdrModeToBytes = {
	{Imp, 1},
	{Acc, 1},
	{Imm, 2},
	{Abs, 3},
	{XIdxAbs, 3},
	{YIdxAbs, 3},
	{AbsInd, 3},
	{ZP, 2},
	{XIdxZP, 2},
	{YIdxZP, 2},
	{XIdxZPInd, 2},
	{ZPIndYIdx, 2},
	{Rel, 2},
};

const std::unordered_map<CPU::CPU_STATE, FunPtr> CPU::CpuStateToFun = {
	{IRQ_SIG, &CPU::IRQ_INT},
	{NMI_SIG, &CPU::NMI_INT},
	{RESET_SIG, &CPU::RESET_INT},
};

// Opcode -> <Cycles, Function, AdrMode>
const std::unordered_map<u8, std::tuple<u8, FunPtr, CPU::ADR_MODE>> CPU::OpTable = {
	{0x00, {7, &CPU::op_brk, Imp}},
	{0x18, {2, &CPU::op_clc, Imp}},
	{0xD8, {2, &CPU::op_cld, Imp}},
	{0x58, {2, &CPU::op_cli, Imp}},
	{0xB8, {2, &CPU::op_clv, Imp}},
	{0xCA, {2, &CPU::op_dex, Imp}},
	{0x88, {2, &CPU::op_dey, Imp}},
	{0xE8, {2, &CPU::op_inx, Imp}},
	{0xC8, {2, &CPU::op_iny, Imp}},
	{0xEA, {2, &CPU::op_nop, Imp}},
	{0x48, {3, &CPU::op_pha, Imp}},
	{0x08, {3, &CPU::op_php, Imp}},
	{0x68, {4, &CPU::op_pla, Imp}},
	{0x28, {4, &CPU::op_plp, Imp}},
	{0x40, {6, &CPU::op_rti, Imp}},
	{0x60, {6, &CPU::op_rts, Imp}},
	{0x38, {2, &CPU::op_sec, Imp}},
	{0xF8, {2, &CPU::op_sed, Imp}},
	{0x78, {2, &CPU::op_sei, Imp}},
	{0xAA, {2, &CPU::op_tax, Imp}},
	{0xA8, {2, &CPU::op_tay, Imp}},
	{0xBA, {2, &CPU::op_tsx, Imp}},
	{0x8A, {2, &CPU::op_txa, Imp}},
	{0x9A, {2, &CPU::op_txs, Imp}},
	{0x98, {2, &CPU::op_tya, Imp}},

	{0xA9, {2, &CPU::op_lda, Imm}},
	{0xA2, {2, &CPU::op_ldx, Imm}},
	{0xA0, {2, &CPU::op_ldy, Imm}},
	{0x29, {2, &CPU::op_and, Imm}},
	{0x49, {2, &CPU::op_eor, Imm}},
	{0x09, {2, &CPU::op_ora, Imm}},
	{0x69, {2, &CPU::op_adc, Imm}},
	{0xC9, {2, &CPU::op_cmp, Imm}},
	{0xE0, {2, &CPU::op_cpx, Imm}},
	{0xC0, {2, &CPU::op_cpy, Imm}},
	{0xE9, {2, &CPU::op_sbc, Imm}},

	{0x0A, {2, &CPU::op_asl, Acc}},
	{0x4A, {2, &CPU::op_lsr, Acc}},
	{0x2A, {2, &CPU::op_rol, Acc}},
	{0x6A, {2, &CPU::op_ror, Acc}},
	{0xAD, {4, &CPU::op_lda, Abs}},
	{0xAE, {4, &CPU::op_ldx, Abs}},
	{0xAC, {4, &CPU::op_ldy, Abs}},
	{0x2D, {4, &CPU::op_and, Abs}},
	{0x2C, {4, &CPU::op_bit, Abs}},
	{0x4D, {4, &CPU::op_eor, Abs}},
	{0x0D, {4, &CPU::op_ora, Abs}},
	{0x6D, {4, &CPU::op_adc, Abs}},
	{0xCD, {4, &CPU::op_cmp, Abs}},
	{0xEC, {4, &CPU::op_cpx, Abs}},
	{0xCC, {4, &CPU::op_cpy, Abs}},
	{0xED, {4, &CPU::op_sbc, Abs}},
	{0x8D, {4, &CPU::op_sta, Abs}},
	{0x8E, {4, &CPU::op_stx, Abs}},
	{0x8C, {4, &CPU::op_sty, Abs}},
	{0x0E, {6, &CPU::op_asl, Abs}},
	{0x4E, {6, &CPU::op_lsr, Abs}},
	{0x2E, {6, &CPU::op_rol, Abs}},
	{0x6E, {6, &CPU::op_ror, Abs}},
	{0xCE, {6, &CPU::op_dec, Abs}},
	{0xEE, {6, &CPU::op_inc, Abs}},

	{0xBD, {4, &CPU::op_lda, XIdxAbs}},
	{0xBC, {4, &CPU::op_ldy, XIdxAbs}},
	{0x3D, {4, &CPU::op_and, XIdxAbs}},
	{0x5D, {4, &CPU::op_eor, XIdxAbs}},
	{0x1D, {4, &CPU::op_ora, XIdxAbs}},
	{0x7D, {4, &CPU::op_adc, XIdxAbs}},
	{0xDD, {4, &CPU::op_cmp, XIdxAbs}},
	{0xFD, {4, &CPU::op_sbc, XIdxAbs}},
	{0x9D, {5, &CPU::op_sta, XIdxAbs}},
	{0x1E, {7, &CPU::op_asl, XIdxAbs}},
	{0x5E, {7, &CPU::op_lsr, XIdxAbs}},
	{0x3E, {7, &CPU::op_rol, XIdxAbs}},
	{0x7E, {7, &CPU::op_ror, XIdxAbs}},
	{0xDE, {7, &CPU::op_dec, XIdxAbs}},
	{0xFE, {7, &CPU::op_inc, XIdxAbs}},

	{0xB9, {4, &CPU::op_lda, YIdxAbs}},
	{0xBE, {4, &CPU::op_ldx, YIdxAbs}},
	{0x39, {4, &CPU::op_and, YIdxAbs}},
	{0x59, {4, &CPU::op_eor, YIdxAbs}},
	{0x19, {4, &CPU::op_ora, YIdxAbs}},
	{0x79, {4, &CPU::op_adc, YIdxAbs}},
	{0xD9, {4, &CPU::op_cmp, YIdxAbs}},
	{0xF9, {4, &CPU::op_sbc, YIdxAbs}},
	{0x99, {5, &CPU::op_sta, YIdxAbs}},

	{0xA5, {3, &CPU::op_lda, ZP}},
	{0xA6, {3, &CPU::op_ldx, ZP}},
	{0xA4, {3, &CPU::op_ldy, ZP}},
	{0x25, {3, &CPU::op_and, ZP}},
	{0x24, {3, &CPU::op_bit, ZP}},
	{0x45, {3, &CPU::op_eor, ZP}},
	{0x05, {3, &CPU::op_ora, ZP}},
	{0x65, {3, &CPU::op_adc, ZP}},
	{0xC5, {3, &CPU::op_cmp, ZP}},
	{0xE4, {3, &CPU::op_cpx, ZP}},
	{0xC4, {3, &CPU::op_cpy, ZP}},
	{0xE5, {3, &CPU::op_sbc, ZP}},
	{0x85, {3, &CPU::op_sta, ZP}},
	{0x86, {3, &CPU::op_stx, ZP}},
	{0x84, {3, &CPU::op_sty, ZP}},
	{0x06, {5, &CPU::op_asl, ZP}},
	{0x46, {5, &CPU::op_lsr, ZP}},
	{0x26, {5, &CPU::op_rol, ZP}},
	{0x66, {5, &CPU::op_ror, ZP}},
	{0xC6, {5, &CPU::op_dec, ZP}},
	{0xE6, {5, &CPU::op_inc, ZP}},

	{0xB5, {4, &CPU::op_lda, XIdxZP}},
	{0xB4, {4, &CPU::op_ldy, XIdxZP}},
	{0x35, {4, &CPU::op_and, XIdxZP}},
	{0x55, {4, &CPU::op_eor, XIdxZP}},
	{0x15, {4, &CPU::op_ora, XIdxZP}},
	{0x75, {4, &CPU::op_adc, XIdxZP}},
	{0xD5, {4, &CPU::op_cmp, XIdxZP}},
	{0xF5, {4, &CPU::op_sbc, XIdxZP}},
	{0x95, {4, &CPU::op_sta, XIdxZP}},
	{0x94, {4, &CPU::op_sty, XIdxZP}},
	{0x16, {6, &CPU::op_asl, XIdxZP}},
	{0x56, {6, &CPU::op_lsr, XIdxZP}},
	{0x36, {6, &CPU::op_rol, XIdxZP}},
	{0x76, {6, &CPU::op_ror, XIdxZP}},
	{0xD6, {6, &CPU::op_dec, XIdxZP}},
	{0xF6, {6, &CPU::op_inc, XIdxZP}},

	{0xB6, {4, &CPU::op_ldx, YIdxZP}},
	{0x96, {4, &CPU::op_stx, YIdxZP}},

	{0xA1, {6, &CPU::op_lda, XIdxZPInd}},
	{0x21, {6, &CPU::op_and, XIdxZPInd}},
	{0x41, {6, &CPU::op_eor, XIdxZPInd}},
	{0x01, {6, &CPU::op_ora, XIdxZPInd}},
	{0x61, {6, &CPU::op_adc, XIdxZPInd}},
	{0xC1, {6, &CPU::op_cmp, XIdxZPInd}},
	{0xE1, {6, &CPU::op_sbc, XIdxZPInd}},
	{0x81, {6, &CPU::op_sta, XIdxZPInd}},

	{0xB1, {5, &CPU::op_lda, ZPIndYIdx}},
	{0x31, {5, &CPU::op_and, ZPIndYIdx}},
	{0x51, {5, &CPU::op_eor, ZPIndYIdx}},
	{0x11, {5, &CPU::op_ora, ZPIndYIdx}},
	{0x71, {5, &CPU::op_adc, ZPIndYIdx}},
	{0xD1, {5, &CPU::op_cmp, ZPIndYIdx}},
	{0xF1, {5, &CPU::op_sbc, ZPIndYIdx}},
	{0x91, {6, &CPU::op_sta, ZPIndYIdx}},

	{0x4C, {3, &CPU::op_jmp, Abs}},
	{0x20, {6, &CPU::op_jsr, Abs}},

	{0x6C, {5, &CPU::op_jmp, AbsInd}},

	{0x90, {2, &CPU::op_bcc, Rel}},
	{0xB0, {2, &CPU::op_bcs, Rel}},
	{0xF0, {2, &CPU::op_beq, Rel}},
	{0x30, {2, &CPU::op_bmi, Rel}},
	{0xD0, {2, &CPU::op_bne, Rel}},
	{0x10, {2, &CPU::op_bpl, Rel}},
	{0x50, {2, &CPU::op_bvc, Rel}},
	{0x70, {2, &CPU::op_bvs, Rel}},

	// Undocumented
	{0x02, {0, &CPU::op_jam, Imp}},
	{0x12, {0, &CPU::op_jam, Imp}},
	{0x22, {0, &CPU::op_jam, Imp}},
	{0x32, {0, &CPU::op_jam, Imp}},
	{0x42, {0, &CPU::op_jam, Imp}},
	{0x52, {0, &CPU::op_jam, Imp}},
	{0x62, {0, &CPU::op_jam, Imp}},
	{0x72, {0, &CPU::op_jam, Imp}},
	{0x92, {0, &CPU::op_jam, Imp}},
	{0xB2, {0, &CPU::op_jam, Imp}},
	{0xD2, {0, &CPU::op_jam, Imp}},
	{0xF2, {0, &CPU::op_jam, Imp}},
};

using namespace Symbols;

const std::unordered_map<FunPtr, Symbols::OP_SYM, CPU::FunPtrHasher> CPU::opcodeFunToSym = {
	{&CPU::op_and, AND},
	{&CPU::op_bit, BIT},
	{&CPU::op_eor, EOR},
	{&CPU::op_ora, ORA},

	// Arith:
	{&CPU::op_adc, ADC},
	{&CPU::op_cmp, CMP},
	{&CPU::op_cpx, CPX},
	{&CPU::op_cpy, CPY},
	{&CPU::op_sbc, SBC},

	// Shift:
	{&CPU::op_asl, ASL},
	{&CPU::op_lsr, LSR},
	{&CPU::op_rol, ROL},
	{&CPU::op_ror, ROR},

	// Bra:
	{&CPU::op_bcc, BCC},
	{&CPU::op_bcs, BCS},
	{&CPU::op_beq, BEQ},
	{&CPU::op_bmi, BMI},
	{&CPU::op_bne, BNE},
	{&CPU::op_bpl, BPL},
	{&CPU::op_bvc, BVC},
	{&CPU::op_bvs, BVS},

	// Ctrl:
	{&CPU::op_brk, BRK},
	{&CPU::op_jmp, JMP},
	{&CPU::op_jsr, JSR},
	{&CPU::op_rti, RTI},
	{&CPU::op_rts, RTS},

	// Flags:
	{&CPU::op_clc, CLC},
	{&CPU::op_cld, CLD},
	{&CPU::op_cli, CLI},
	{&CPU::op_clv, CLV},
	{&CPU::op_sec, SEC},
	{&CPU::op_sed, SED},
	{&CPU::op_sei, SEI},

	// Inc:
	{&CPU::op_dec, DEC},
	{&CPU::op_dex, DEX},
	{&CPU::op_dey, DEY},
	{&CPU::op_inc, INC},
	{&CPU::op_inx, INX},
	{&CPU::op_iny, INY},

	// Load:
	{&CPU::op_lda, LDA},
	{&CPU::op_ldx, LDX},
	{&CPU::op_ldy, LDY},
	{&CPU::op_sta, STA},
	{&CPU::op_stx, STX},
	{&CPU::op_sty, STY},

	// Stack:
	{&CPU::op_pha, PHA},
	{&CPU::op_php, PHP},
	{&CPU::op_pla, PLA},
	{&CPU::op_plp, PLP},

	// Trans:
	{&CPU::op_tax, TAX},
	{&CPU::op_tay, TAY},
	{&CPU::op_tsx, TSX},
	{&CPU::op_txa, TXA},
	{&CPU::op_txs, TXS},
	{&CPU::op_tya, TYA},

	// Nop:
	{&CPU::op_nop, NOP},

	// Undocumented
	{&CPU::op_jam, JAM},
};