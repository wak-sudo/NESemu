#include "CPU.h"

void CPU::op_clc() { Flags.setFlagCarry(0); }

void CPU::op_cld() { Flags.setFlagDecimal(0); }

void CPU::op_cli() { Flags.setFlagInd(0); }

void CPU::op_clv() { Flags.setFlagOverflow(0); }

void CPU::op_sec() { Flags.setFlagCarry(1); }

void CPU::op_sed() { Flags.setFlagDecimal(1); }

void CPU::op_sei() { Flags.setFlagInd(1); }