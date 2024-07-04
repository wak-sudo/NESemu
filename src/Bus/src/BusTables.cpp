#include "Bus.h"

const std::unordered_map<Bus::PORTS, PPU::writeFun> Bus::PPUregWriteToFun = {
	{PPUCTRL, &PPU::writePPUCTRL},
	{PPUMASK, &PPU::writePPUMASK},
	{OAMADDR, &PPU::writeOAMADDR},
	{OAMDATA, &PPU::writeOAMDATA},
	{PPUSCROLL, &PPU::writePPUSCROLL},
	{PPUADDR, &PPU::writePPUADDR},
	{PPUDATA, &PPU::writePPUDATA},
	//{OAMDMA, &PPU::writeOAMDMA}, // different kind
};

const std::unordered_map<Bus::PORTS, PPU::readFun> Bus::PPUregReadToFun = {
	{PPUSTATUS, &PPU::readPPUSTATUS},
	{OAMDATA, &PPU::readOAMDATA},
	{PPUDATA, &PPU::readPPUDATA},
};