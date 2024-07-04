#include "CPU.h"

void CPU::setFlagsBit(u8 index, u8 val)
{
	if (val == 0) Flags &= ~(1 << index);
	else Flags |= 1 << index;
}

u8 CPU::getFlagsBit(u8 index) { return (Flags >> index) & 1; }

void CPU::set_carry(u8 val) { setFlagsBit(0, val); }
u8 CPU::get_carry() { return getFlagsBit(0); }

void CPU::set_zero(u8 val) { setFlagsBit(1, val); }
u8 CPU::get_zero() { return getFlagsBit(1); }

// Interrupt Disable
void CPU::set_ind(u8 val) { setFlagsBit(2, val); }
u8 CPU::get_ind() { return getFlagsBit(2); }

void CPU::set_decimal(u8 val) { setFlagsBit(3, val); }
u8 CPU::get_decimal() { return getFlagsBit(3); }

void CPU::set_break(u8 val) { setFlagsBit(4, val); }
u8 CPU::get_break() { return getFlagsBit(4); }

// Bit 5 - unused?

void CPU::set_overflow(u8 val) { setFlagsBit(6, val); }
u8 CPU::get_overflow() { return getFlagsBit(6); }

void CPU::set_negative(u8 val) { setFlagsBit(7, val); }
u8 CPU::get_negative() { return getFlagsBit(7); }


void CPU::checkCarry(u16 res)
{
	set_carry(res > 255);
}

void CPU::checkNegative(u8 arg)
{
	set_negative((i8)arg < 0);
}

void CPU::checkOverflow(u8 res, u8 a, u8 b)
{
	set_overflow(((b ^ res) & (a ^ res) & 0x80) >> 7);
}

void CPU::checkZero(u8 arg)
{
	set_zero(arg == 0);
}