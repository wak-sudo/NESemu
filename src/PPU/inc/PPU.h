#pragma once

#include "Global.h"

#include <string>

class PPU
{
public:
	PPU();
	~PPU();

	using readFun = u8(PPU::*)();
	using writeFun = void (PPU::*)(u8 arg);

	u8 getBit(u8 val, u8 index);
	void replaceBit(u8* dst, u8 index, u8 val);

	void writePPUCTRL(u8 val);
	void writePPUMASK(u8 val);
	u8 readPPUSTATUS();
	void writeOAMADDR(u8 val);
	void writeOAMDATA(u8 val);
	u8 readOAMDATA();
	void writePPUSCROLL(u8 val);
	void writePPUADDR(u8 val);
	void writePPUDATA(u8 val);
	u8 readPPUDATA();
	void writeOAMDMA(u8 adr, u8* mem);

	void writeVRAM(u16 adr, u8 val);
	u8 readVRAM(u16 adr);

	void loadCHRROMbank(i8* src);

	void render();

	const u16 disHeight = 240;
	const u16 disWidth = 256;
	u8** display;

	void allocateDisplay();
	void deallocateDisplay();

	void loadPalette(const char* filePath);

private:
	const u16 vramSize = 16 * KB;
	const u16 oamRamSize = 256;

	const u8 displayWidth = 32; // those are in tiles.
	const u8 displayHeight = 30;

	// Memory map:

	const u16 patTablesStart = 0;
	const u16 patTablesEnd = 0x2000;

	const u16 onePatTableSize = 0x1000;
	const u16 totalPatTableSize = 0x2000;
	const u16 nameTabSize = 0x3c0;
	const u16 attTabSize = 0x40;

	const u16 patTabAdr[2] = { 0, 0x1000 };
	const u16 nameTabAdr[4] = { 0x2000, 0x2400, 0x2800, 0x2C00 };
	const u16 attTabAdr[4] = { 0x23c0, 0x27c0, 0x2bc0, 0x2fc0 };


	// First sector is Nametables, Atr tables and their mirrors.
	const u16 actNametabSectorSize = 0x1000;
	const u16 nametabSectorStart = 0x2000;
	const u16 nametabSectorEnd = 0x3F00;

	// Second sector is Palletes and their mirror.
	const u16 actPalleteSectorSize = 0x20;
	const u16 paletteSectorStart = 0x3f00;
	const u16 paletteSectorEnd = 0x4000;

	const u16 actAllSectorsSize = 0x4000;

	// PPUCTRL
	struct
	{
		union
		{
			struct
			{
				u16 baseNametableAdr : 2;
				u8 vramIncrementStep : 1;
				u16 spritePatternTableAdr : 1;
				u16 bckgrdPatternTableAdr : 1;
				u8 spriteSize : 1;
				u8 slaveMode : 1;
				u8 generateNMI : 1;
			};
			u8 reg;
		};

		void write(u8 val) { reg = val; }
	} RegPPUCTRL;


	// PPUMASK

	union
	{
		struct
		{
			u8 greyScale : 1;
			u8 shBackLeft : 1;
			u8 shSpritesLeft : 1;
			u8 showBck : 1;
			u8 showSprites : 1;
			u8 emphRed : 1;
			u8 emphGreen : 1;
			u8 emphBlue : 1;
		};
		u8 reg;

		void write(u8 val) { reg = val; }
	} RegPPUMASK;

	union
	{
		struct
		{
			u8 openBus : 5;
			u8 spirteOverflow : 1;
			u8 spriteZeroHit : 1;
			u8 vBlank : 1;
		};
		u8 reg;

		u8 read() {
			u8 ret = reg;
			vBlank = 0;
			return ret;
		}
	} RegPPUSTATUS;

	// oam address and data

	class TwiceWriter
	{
		u8 idx = 0;
	public:
		u8 arr[2];
		void write(u8 val)
		{
			arr[idx] = val;
			idx = (idx + 1) % 2;
		}
	};

	TwiceWriter RegPPUSCROLL;

	TwiceWriter RegPPUADDR;

	u8 oamAdrPtr = 0;

	// VRAM:
	u8* patternTableMem;
	u8* nametabSectorMem;
	u8* paletteSectorMem;
	u8* oamRam;
	//u8* display;

	enum PALETTE_ADR {
		UNI_BCK_COLOR = 0x3F00,
		BCK_PALETTE_0 = 0x3F01,
		BCK_PALETTE_1 = 0x3F05,
		BCK_PALETTE_2 = 0x3F09,
		BCK_PALETTE_3 = 0x3F0D,
		SPR_PALETTE_0 = 0x3F11,
		SPR_PALETTE_1 = 0x3F15,
		SPR_PALETTE_2 = 0x3F19,
		SPR_PALETTE_3 = 0x3F1D,
	};

	const u8 paletteSize = 64;
	std::string sysPalett[64];
	const char* paletteErroMsg = "Unable to load a palette.";

	// Internal
	u16 RegV;
	u16 RegT;
	u8 RegX;
	u8 RegW;
};

