#include "CPU.h"

// Decimal mode is not taken into account.

void CPU::cmpGeneric(u8 reg, u8 arg)
{
	u8 res = reg - arg;
	checkZero(res);
	checkNegative(res);
	set_carry(arg <= reg);
}

void CPU::op_cmp(u8 arg) { cmpGeneric(RegA, arg); }

void CPU::op_cpx(u8 arg) { cmpGeneric(RegX, arg); }

void CPU::op_cpy(u8 arg) { cmpGeneric(RegY, arg); }

void CPU::op_adc(u8 arg)
{
	u16 res = RegA + arg + get_carry();
	checkOverflow((u8)res, RegA, arg);
	checkCarry(res);
	checkNegative((u8)res);
	checkZero((u8)res);
	RegA = (u8)res;
}

void CPU::op_sbc(u8 arg)
{
	u16 res = RegA - arg - ~get_carry();
	set_carry(res >= 0);
	checkOverflow((u8)res, RegA, arg);
	checkNegative((u8)res);
	checkZero((u8)res);
	RegA = (u8)res;
}
