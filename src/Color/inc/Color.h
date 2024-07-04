#pragma once

#include <string>

#include "Global.h"

class Color
{
	u8 red_;
	u8 green_;
	u8 blue_;

	std::string toHex(u8 val) const;
public:
	Color(u8 red, u8 green, u8 blue) : red_(red), green_(green), blue_(blue) {}
	std::string toHTML() const; // without hashtag for now.
	u8 red() const;
	u8 green() const;
	u8 blue() const;
};