#pragma once

#include "Global.h"

class FlagsReg
{
	const u8 DEFAULT_VAL = 0x34;

	u8 reg = DEFAULT_VAL;

	void setFlagsBit(u8 index, bool val);
	u8 getFlagsBit(u8 index);

public:
	u8 getFlagZero();
	u8 getFlagCarry();
	u8 getFlagInd();
	u8 getFlagDecimal();
	u8 getFlagBreak();
	u8 getFlagOverflow();
	u8 getFlagNegative();

	u8 getVal();
	void setVal(u8 val);

	void setFlagZero(bool val);
	void setFlagInd(bool val); // Interrupt Disable
	void setFlagDecimal(bool val);
	void setFlagBreak(bool val);
	// bit 5 - unused?
	void setFlagCarry(bool val);
	void setFlagOverflow(bool val);
	void setFlagNegative(bool val);

	// Tests provided value/s and changes corresponding flags.
	void testNegative(u8 arg);
	void testOverflow(u8 res, u8 a, u8 b);
	void testCarry(u16 res);
	void testZero(u8 arg);

	void reset();
};