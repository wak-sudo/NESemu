#include "CPU.h"

#include <iostream>

#include "Debugger.h"

using namespace std;

int main()
{
	u64 memSize = 0xFFFF + 1;
	u8 *mem = new u8[memSize];
	CPU MOSCPU(mem, memSize);

	bool loadBin = false;
	if (loadBin)
		MOSCPU.LoadBinary("prog.bin", 0x0200);

	/*while (MOSCPU.getState() != CPU::POWER_OFF)
	{
		const u8 regA = MOSCPU.getRegA();
		const u8 regX = MOSCPU.getRegX();
		const u8 regY = MOSCPU.getRegY();
		const u8 regSP = MOSCPU.getRegSP();
		const u16 regPC = MOSCPU.getRegPC();
		const u8 reg = MOSCPU.getRegFlags();
		const CPU::CPU_STATE state = MOSCPU.getState();
	}*/

	//ImGui::ShowDemoWindow();

	Debugger debProg(&MOSCPU, mem, memSize);
	debProg.show();

	delete[] mem;

	return 0;
}
