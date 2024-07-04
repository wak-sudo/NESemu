#pragma once

#define KB 1024

#include <fstream>
#include "Global.h"

#include "Bus.h"

class Mapper
{
public:
	Mapper(const char* filePath);
	~Mapper();

	void loadRom(const char* filePath);

	u8 unitsOfPRGROM() const;
	u8 sizeOfPRGROM() const;
	u8 unitsOfCHRROM() const;
	u8 sizeOfCHRROM() const;

	u8 getPRGROM(unsigned index, unsigned addr) const;
	u8 getCHRROM(unsigned index, unsigned addr) const;

	i8* getPRGROMptr(unsigned index) const;
	i8* getCHRROMptr(unsigned index) const;

private:
//	friend void Bus::loadPRGROMbank(u8 index, bool lower);
//	friend void Bus::loadCHRROMbank(u8 index);

	void checkMagic(i8* header);
	void updateFlags(i8* header);
	void updatePointers(std::ifstream& file);

	void setUnitsOfPRGROM(u8 val);
	void setUnitsOfCHRROM(u8 val);

	void deallocateData();
	u8 getBit(u8 val, u8 index);

	const u16 PRGROMunitSize = 16 * KB;
	const u16 CHRROMunitSize = 8 * KB;

	const u8 headerSize = 16;
	const u16 trainerSize = 512;

	const u8 magicSeqLen = 4;
	unsigned magicSeq[4] = { 0x4E, 0x45, 0x53, 0x1A };

	const char* errorMsg = "It's not a NES rom.";

	//  PlayChoice is omitted.

	// Header
	// DO NOT CHANGE THEM DIRECTLY, USE FUNCTIONS.
	u8 unitsOfPRGROM_ = 0;
	unsigned sizeOfPRGROM_ = 0;
	u8 unitsOfCHRROM_ = 0;
	unsigned sizeOfCHRROM_ = 0;
	//

	i8* PRGROMdata = nullptr;
	i8* CHROMdata = nullptr;

	//unsigned sizeOfPRGRAM; // how to know it?

	u8 flag6 = 0;
	u8 trainerPresent = 0;
	u8 flag7 = 0;
	u8 flag8 = 0;
	u8 flag9 = 0;
	u8 flag10 = 0;
};

