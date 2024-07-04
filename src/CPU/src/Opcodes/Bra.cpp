#include "CPU.h"

void CPU::branchGeneric(u8 flag, bool test, u16 adr)
{
	if (flag == (u8)test)
		PC = adr;
}

void CPU::op_bcs(u16 arg) { branchGeneric(get_carry(), 1, arg); }

void CPU::op_bcc(u16 arg) { branchGeneric(get_carry(), 0, arg); }

void CPU::op_beq(u16 arg) { branchGeneric(get_zero(), 1, arg); }

void CPU::op_bne(u16 arg) { branchGeneric(get_zero(), 0, arg); }

void CPU::op_bmi(u16 arg) { branchGeneric(get_negative(), 1, arg); }

void CPU::op_bpl(u16 arg) { branchGeneric(get_negative(), 0, arg); }

void CPU::op_bvs(u16 arg) { branchGeneric(get_overflow(), 1, arg); }

void CPU::op_bvc(u16 arg) { branchGeneric(get_overflow(), 0, arg); }
