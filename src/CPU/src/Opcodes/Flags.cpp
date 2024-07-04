#include "CPU.h"

void CPU::op_clc() { set_carry(0); }

void CPU::op_cld() { set_decimal(0); }

void CPU::op_cli() { set_ind(0); }

void CPU::op_clv() { set_overflow(0); }

void CPU::op_sec() { set_carry(1); }

void CPU::op_sed() { set_decimal(1); }

void CPU::op_sei() { set_ind(1); }