#pragma once

#include "CPU.h"
#include "PPU.h"
#include "Mapper.h"

#include "Global.h"

class Bus
{
public:
	Bus(const char* filePath);
	~Bus();

	void changeRom(const char* filePath);
	void startFlow();

	enum PORTS
	{
		// PPU ports:
		PPUCTRL = 0x2000,
		PPUMASK = 0x2001,
		PPUSTATUS = 0x2002,
		OAMADDR = 0x2003,
		OAMDATA = 0x2004,
		PPUSCROLL = 0x2005,
		PPUADDR = 0x2006,
		PPUDATA = 0x2007,
		OAMDMA = 0x4014,

		// IO and APU ports:
		SQ1_VOL = 0x4000,
		SQ1_SWEEP = 0x4001,
		SQ1_LO = 0x4002,
		SQ1_HI = 0x4003,
		SQ2_VOL = 0x4004,
		SQ2_SWEEP = 0x4005,
		SQ2_LO = 0x4006,
		SQ2_HI = 0x4007,
		TRI_LINEAR = 0x4008,
		TRI_LO = 0x400A,
		TRI_HI = 0x400B,
		NOISE_VOL = 0x400C,
		NOISE_LO = 0x400E,
		NOISE_HI = 0x400F,
		DMC_FREQ = 0x4010,
		DMC_RAW = 0x4011,
		DMC_START = 0x4012,
		DMC_LEN = 0x4013,
		SND_CHN = 0x4015,
		JOY1 = 0x4016,
		JOY2 = 0x4017,
	};

private:
	void prepareMem();
	void loadPRGROMbank(u8 index, bool lower);

	void CPUwrite(u16 addr, u8 val);
	u8 CPUread(u16 addr);

	// Handle PPU registers;
	static const std::unordered_map<PORTS, PPU::writeFun> PPUregWriteToFun;
	static const std::unordered_map<PORTS, PPU::readFun> PPUregReadToFun;

	const unsigned actRamSize = 2 * KB;

	// ram + mirror
	const u16 ramSectorStart = 0;
	const u16 ramSectorEnd = 0x2000;

	// ppu regs + their mirror
	const u16 actPPURegSectorSize = 0x8;
	const u16 ppuRegSectorStart = 0x2000;
	const u16 ppuRegSectorEnd = 0x4000;

	// IO & APU regs + ExpRom + SRAM + PRG-ROM banks.
	const u16 sectorThreeSize = 0xC000;

	// exp rom
	const u16 expRomStart = 0x4020;
	const u16 expRomEnd = 0x6000;

	// sram
	const u16 sramStart = 0x6000;
	const u16 sramEnd = 0x8000;

	// prg-rom banks
	const u16 prgRomLowBankStart = sramStart;
	const u16 prgRomLowBankEnd = 0xC000;
	const u16 prgRomUppBankStart = prgRomLowBankEnd;
	const unsigned prgRomUppBankEnd = 0x10000;

	// Memory:
	u8* RAM = nullptr; // Ram without mirror
	u8* ppuRegSectorMem = nullptr; // PPU registers without mirror.
	u8* sectorThreeMem = nullptr; // IO & APU registers, ExpRom, CHRRAM, PRG-ROM banks.

	CPU* MOS = nullptr;
	PPU* Graph = nullptr;
	Mapper* MAP = nullptr;

	u8 curPRGBankLow = 0;
	u8 curPRGBankHig = 0;
	u8 curCHRBank = 0;
};

