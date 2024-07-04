#include "PPU.h"

PPU::PPU()
{
	patternTableMem = new u8[totalPatTableSize];
	nametabSectorMem = new u8[actNametabSectorSize];
	paletteSectorMem = new u8[actPalleteSectorSize];
	oamRam = new u8[oamRamSize];
	allocateDisplay();
}

PPU::~PPU()
{
	delete[] patternTableMem;
	delete[] nametabSectorMem;
	delete[] paletteSectorMem;
	delete[] oamRam;
	deallocateDisplay();
}

u8 PPU::getBit(u8 val, u8 index)
{
	return (val >> index) & 1;
}

void PPU::replaceBit(u8* dst, u8 index, u8 val)
{
	if (val == 0) *dst &= ~(1 << index);
	else *dst |= 1 << index;
}

void PPU::allocateDisplay()
{
	display = new u8 * [disHeight];
	for (size_t i = 0; i < disHeight; i++)
		display[i] = new u8[disWidth];
}

void PPU::deallocateDisplay()
{
	for (size_t i = 0; i < disHeight; i++)
			delete[] display[i];
}