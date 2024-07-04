#include "Bus.h"

#define KB 1024

Bus::Bus(const char* filePath)
{
	RAM = new u8[actRamSize];
	ppuRegSectorMem = new u8[actPPURegSectorSize];
	sectorThreeMem = new u8[sectorThreeSize];
	MOS = new CPU(RAM, actRamSize);
	Graph = new PPU();
	MAP = new Mapper(filePath);
}

Bus::~Bus()
{
	delete[] RAM;
	delete[] ppuRegSectorMem;
	delete[] sectorThreeMem;
	delete MOS;
	delete Graph;
	delete MAP;
}