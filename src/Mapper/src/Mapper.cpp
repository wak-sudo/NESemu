#include "Mapper.h"

void Mapper::setUnitsOfPRGROM(u8 val)
{
	unitsOfPRGROM_ = val;
	sizeOfPRGROM_ = (unsigned)unitsOfPRGROM_ * PRGROMunitSize;
}

void Mapper::setUnitsOfCHRROM(u8 val)
{
	if (val == 0) throw std::runtime_error("PRG RAM unimplemented.");
	unitsOfCHRROM_ = val;
	sizeOfCHRROM_ = (unsigned)unitsOfCHRROM_ * CHRROMunitSize;
}

u8 Mapper::getBit(u8 val, u8 index)
{
	return (val >> index) & 1;
}

u8 Mapper::unitsOfPRGROM() const { return unitsOfPRGROM_; }
u8 Mapper::sizeOfPRGROM() const { return sizeOfPRGROM_; }
u8 Mapper::unitsOfCHRROM() const { return unitsOfCHRROM_; }
u8 Mapper::sizeOfCHRROM() const { return sizeOfCHRROM_; }

u8 Mapper::getPRGROM(unsigned index, unsigned addr) const { return PRGROMdata[index * sizeOfPRGROM_ + addr]; };
u8 Mapper::getCHRROM(unsigned index, unsigned addr) const { return CHROMdata[index * sizeOfCHRROM_ + addr]; }

i8* Mapper::getCHRROMptr(unsigned index) const { return &CHROMdata[sizeOfCHRROM_ * index]; }
i8* Mapper::getPRGROMptr(unsigned index) const { return &PRGROMdata[sizeOfPRGROM_ * index]; }


