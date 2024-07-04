#include "Mapper.h"

void Mapper::loadRom(const char* filePath)
{
	std::ifstream file(filePath, std::ifstream::binary);
	if (file)
	{
		file.seekg(0, file.end);
		int length = file.tellg();
		file.seekg(0, file.beg);
		if(length < headerSize) throw std::runtime_error(errorMsg);

		i8* header = new i8[16];
		file.read(header, headerSize);
		checkMagic(header);
		updateFlags(header);
		delete[] header;

		if (trainerPresent) file.seekg(trainerSize, std::ios::cur);

		updatePointers(file);

		file.close();
	}
}

void Mapper::checkMagic(i8* header)
{
	for (unsigned i = 0; i < magicSeqLen; i++)
		if (header[i] != magicSeq[i])
			throw std::runtime_error(errorMsg);
}

void Mapper::updateFlags(i8* header)
{
	setUnitsOfPRGROM(header[4]);
	setUnitsOfCHRROM(header[5]);

	flag6 = header[6];
	trainerPresent = getBit(flag6, 3);
	flag7 = header[7];
	flag8 = header[8];
	flag9 = header[9];
	flag10 = header[10];
}

void Mapper::updatePointers(std::ifstream& file)
{
	deallocateData();

	PRGROMdata = new i8[sizeOfPRGROM_];
	CHROMdata = new i8[sizeOfCHRROM_];

	// we read all banks at once.
	file.read(PRGROMdata, sizeOfPRGROM_);
	file.read(CHROMdata, sizeOfCHRROM_);
}