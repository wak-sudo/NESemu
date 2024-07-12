#pragma once

#include "Util.h"

class FlagsReg
{
	const u8 DEFAULT_VAL = 0x34;

	u8 reg = DEFAULT_VAL;

	void setFlagsBit(u8 index, bool val);
	u8 getFlagsBit(u8 index) const;

public:
	u8 getFlagZero() const;
	u8 getFlagCarry() const;
	u8 getFlagInd() const;
	u8 getFlagDecimal() const;
	u8 getFlagBreak() const;
	u8 getFlagUnused() const;
	u8 getFlagOverflow() const;
	u8 getFlagNegative() const;

	u8 getVal() const;
	void setVal(u8 val);

	void setFlagZero(bool val);
	void setFlagInd(bool val); // Interrupt Disable
	void setFlagDecimal(bool val);
	void setFlagBreak(bool val);
	void setFlagUnused(bool val);
	void setFlagCarry(bool val);
	void setFlagOverflow(bool val);
	void setFlagNegative(bool val);

	// Tests provided value/s and changes corresponding flags.
	void testNegative(u8 arg);
	void testOverflow(u8 res, u8 a, u8 b);
	void testCarry(u16 res);
	void testZero(u8 arg);

	FlagsReg& operator=(const FlagsReg& other);

	void reset();
};