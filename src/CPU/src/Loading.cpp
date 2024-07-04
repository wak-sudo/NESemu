#include "CPU.h"

#include <fstream>
#include <stdexcept>

void CPU::LoadBinary(std::string filePath, u16 startingPoint)
{
	u16 freeSpace = RESET_VECTOR - startingPoint;
	std::ifstream file(filePath, std::ios::binary);
	if (!file.good())
		throw std::runtime_error("Error while reading a file.");
	file.seekg(0, file.end);
	std::streamoff fileLength = file.tellg();
	file.seekg(0, file.beg);
	if(freeSpace < fileLength) throw std::runtime_error("The file is too big.");
	file.read((char*)(Memory + startingPoint), fileLength);
	if (!file) throw std::runtime_error("File at file loading.");

	u8 startLow = (u8)startingPoint;
	u8 startHigh = startingPoint >> 8;
	Memory[RESET_VECTOR] = Memory[IRQ_VECTOR] = startLow;
	Memory[RESET_VECTOR+1] = Memory[IRQ_VECTOR+1] = startHigh;
}