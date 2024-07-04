#include "Mapper.h"

void Mapper::deallocateData()
{
	if (PRGROMdata != nullptr)
	{
		delete[] PRGROMdata;
		PRGROMdata = nullptr;
	}

	if (CHROMdata != nullptr)
	{
		delete[] CHROMdata;
		CHROMdata = nullptr;
	}
}

Mapper::~Mapper()
{
	deallocateData();
}

Mapper::Mapper(const char* filePath)
{
	loadRom(filePath);
}