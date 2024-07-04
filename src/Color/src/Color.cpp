#include "Color.h"

u8 Color::red() const { return red_; }
u8 Color::green() const { return green_; }
u8 Color::blue() const { return blue_; }

std::string Color::toHTML() const
{
	return toHex(red_) + toHex(green_) + toHex(blue_);
}

std::string Color::toHex(u8 val) const
{
	const char hexSys[6] = {
		'A', 'B', 'C', 'D', 'E', 'F'
	};

	std::string res = "";
	while (val != 0)
	{
		u8 rem = val % 16;
		res = (rem > 9 ? hexSys[rem - 10] : (char)(rem + '0')) + res;
		val /= 16;
	}
	return res;
}
