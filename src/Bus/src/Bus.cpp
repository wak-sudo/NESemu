#include "Bus.h"

u8 Bus::CPUread(u16 addr)
{
	if (addr >= ramSectorStart && addr < ramSectorEnd) return RAM[(addr % actRamSize) + ramSectorStart];
	if (addr >= ppuRegSectorStart && addr < ppuRegSectorEnd)
	{
		addr = (addr % actPPURegSectorSize) + ppuRegSectorStart;
		auto it = PPUregReadToFun.find(static_cast<PORTS>(addr));
		if (it != PPUregReadToFun.end()) return (Graph->*(it->second))();
		else return ppuRegSectorMem[addr];
	}
	return sectorThreeMem[addr];
}

void Bus::CPUwrite(u16 addr, u8 val)
{
	if (addr >= ramSectorStart && addr < ramSectorEnd) RAM[(addr % actRamSize) + ramSectorStart] = val;
	else if (addr >= ppuRegSectorStart && addr < ppuRegSectorEnd)
	{
		addr = (addr % actPPURegSectorSize) + ppuRegSectorStart;
		auto it = PPUregWriteToFun.find(static_cast<PORTS>(addr));
		if (it != PPUregWriteToFun.end()) (Graph->*(it->second))(val);
		ppuRegSectorMem[addr] = val;
	}
	else
	{
		if (addr == OAMDMA)
		{
			u8* ptr = RAM;
			if (val >= 20) ptr = ppuRegSectorMem;
			if (val >= 40) ptr = sectorThreeMem;
			Graph->writeOAMDMA(val, ptr);
		}
		sectorThreeMem[addr] = val;
	}
}

void Bus::loadPRGROMbank(u8 index, bool lower)
{
	unsigned startAdr = prgRomUppBankStart;
	unsigned endAdr = prgRomUppBankEnd;

	if (lower)
	{
		startAdr = prgRomLowBankStart;
		endAdr = prgRomLowBankEnd;
	}

	const i8* src = MAP->getPRGROMptr(index);

	for (unsigned i = startAdr; i < endAdr; i++)
		sectorThreeMem[i] = src[i - startAdr];
}

void Bus::changeRom(const char* filePath)
{
	MAP->loadRom(filePath);
}

void Bus::startFlow()
{
	prepareMem();
}

void Bus::prepareMem()
{
	if (MAP->unitsOfPRGROM() == 1)
	{
		loadPRGROMbank(0, true);
		loadPRGROMbank(0, false);
	}
	else throw std::runtime_error("More than 1 unit of PRGROM.");
	for (unsigned i = ppuRegSectorStart; i < ppuRegSectorEnd; i++)
		ppuRegSectorMem[i] = 0;
	Graph->loadCHRROMbank(MAP->getCHRROMptr(0));
	Graph->loadPalette("NTSC.pal"); // hardcoded.
}
