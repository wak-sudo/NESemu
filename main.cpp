#include "CPU.h"

#include <iostream>

#include "DebuggerImgui.h"
#include "RomLoader.h"

using namespace std;

int main()
{
	const u64 memSize = 0xFFFF + 1;
	u8 *mem = new u8[memSize];

	const bool loadBin = true;
	if (loadBin)
	{
		const u16 entryPoint = 0x2000;
		RomLoader::loadFileToMemory("../ROMs/progA.bin", mem, memSize, entryPoint);
		RomLoader::writeVectorsToRom(mem, entryPoint);
	}

	CPU MOSCPU(mem, memSize);

	DebuggerImgui debProg(&MOSCPU, mem, memSize);
	debProg.show();

	delete[] mem;

	return 0;
}
