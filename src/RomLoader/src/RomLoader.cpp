#include "RomLoader.h"

#include <stdexcept>
#include <iostream>
#include <string>

#include <filesystem>

#include "CPU.h"

void RomLoader::loadFileToMemory(const char *filePath, u8 *mem, u64 memSize)
{
    // doesn't work.
    std::ifstream file(filePath, std::ios::binary);
    if (!file.good())
        throw std::runtime_error("Error while reading a file.");
    unsigned long fileLength = std::filesystem::file_size(std::filesystem::path(filePath));
    if (fileLength > memSize)
        throw std::runtime_error("The file is too big.");
    file.read((char *)mem, fileLength);
    if (!file)
        throw std::runtime_error("Fail at file loading. " + std::to_string(file.gcount()) + " bytes written");
    file.close();
}

void RomLoader::loadFileToMemory(const char *filePath, u8 *mem, u64 memSize, u16 offset)
{
    u8 *const newMemPtr = mem + offset;
    const u16 newMemSize = memSize - offset;
    loadFileToMemory(filePath, newMemPtr, newMemSize);
}

void RomLoader::writeVectorsToRom(u8 *rom, u16 entryPoint)
{
    const u8 startLow = (u8)entryPoint;
    const u8 startHigh = entryPoint >> 8;
    rom[CPU::RESET_VECTOR] = rom[CPU::IRQ_VECTOR] = startLow;
    rom[CPU::RESET_VECTOR + 1] = rom[CPU::IRQ_VECTOR + 1] = startHigh;
}