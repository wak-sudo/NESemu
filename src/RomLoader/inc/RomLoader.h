#pragma once

#include <fstream>

#include "Util.h"

namespace RomLoader
{
    void loadFileToMemory(const char *filePath, u8 *mem, u64 memSize);
    void loadFileToMemory(const char *filePath, u8 *mem, u64 memSize, u16 offset);
    void writeVectorsToRom(u8 *rom, u16 entryPoint);
};