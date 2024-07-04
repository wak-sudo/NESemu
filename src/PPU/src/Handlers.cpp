#include "PPU.h"

#include <fstream>
#include <stdexcept>

#include "Color.h"

u8 PPU::readPPUSTATUS()
{
	u8 newVal = spirteOverflow << 5;
	newVal |= spriteZeroHit << 6;
	newVal |= verticalBlank << 7;
	return newVal;
}

void PPU::writeOAMADDR(u8 val)
{
	oamAdrPtr = val;
}

void PPU::writeOAMDATA(u8 val)
{
	oamRam[oamAdrPtr] = val;
	oamAdrPtr++;
}

u8 PPU::readOAMDATA()
{
	return oamRam[oamAdrPtr];
}

void PPU::writePPUSCROLL(u8 val)
{
	scrollValIdx = (scrollValIdx + 1) % 2;
	scrollVal[scrollValIdx] = val;
}

void PPU::writePPUADDR(u8 val)
{
	addrValIdx = (addrValIdx + 1) % 2;
	addrVal[addrValIdx] = val;
	videoMemoryAdrPtr = ((u16)addrVal[0] << 8) + addrVal[1];
}

void PPU::writePPUDATA(u8 val)
{
	writeVRAM(videoMemoryAdrPtr, val);
	videoMemoryAdrPtr += vramIncrementStep;
}

u8 PPU::readPPUDATA()
{
	u8 val = readVRAM(videoMemoryAdrPtr);
	videoMemoryAdrPtr += vramIncrementStep;
	return val;
}

void PPU::writeOAMDMA(u8 adr, u8* mem)
{
	for (u16 ptr = 0; ptr <= 0xff; ptr++)
		oamRam[ptr] = mem[((u16)adr << 8) + ptr];
}

void PPU::writeVRAM(u16 adr, u8 val)
{
	adr %= actAllSectorsSize;
	if (adr >= nametabSectorStart && adr < nametabSectorEnd) nametabSectorMem[(adr % actNametabSectorSize) + nametabSectorStart] = val;
	else if (adr >= paletteSectorStart && adr < paletteSectorEnd)
	{
		adr = (adr % actPalleteSectorSize) + paletteSectorStart;
		if (adr % 4 == 0)
		{
			i8 offset = (adr < 0x10 ? 0x10 : -0x10); // if adress is, for an example, 0x3F10, then we also match 0x3F00 and vice versa
			paletteSectorMem[adr + offset] = val; // pallete mirroring.
		}
		paletteSectorMem[adr] = val;
	}
	else patternTableMem[adr] = val;
}

u8 PPU::readVRAM(u16 adr)
{
	adr %= actAllSectorsSize;
	if (adr >= nametabSectorStart && adr < nametabSectorEnd) return nametabSectorMem[(adr % actNametabSectorSize) + nametabSectorStart];
	if (adr >= paletteSectorStart && adr < paletteSectorEnd) return paletteSectorMem[(adr % actPalleteSectorSize) + paletteSectorStart];
	return patternTableMem[adr];
}

void PPU::loadCHRROMbank(i8* src)
{
	const unsigned startAdr = patTablesStart;
	const unsigned endAdr = patTablesEnd;

	for (unsigned i = startAdr; i < endAdr; i++)
		patternTableMem[i] = src[i];
}


void PPU::loadPalette(const char* filePath)
{
	std::ifstream file(filePath);
	if (file)
	{
		file.seekg(0, file.end);
		int length = file.tellg();
		file.seekg(0, file.beg);

		const u8 bufferSize = paletteSize * 3;

		if (length != bufferSize) throw std::runtime_error(paletteErroMsg);

		i8* buffer = new i8[bufferSize];
		file.read(buffer, bufferSize);

		for (unsigned i = 0; i < paletteSize; i++)
		{
			u8 r = buffer[i * 3];
			u8 g = buffer[i * 3 + 1];
			u8 b = buffer[i * 3 + 2];
			sysPalett[i] = Color(r, g, b).toHTML();
		}

		delete[] buffer;
	}
	else throw std::runtime_error(paletteErroMsg);
}