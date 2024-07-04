#include "CPU.h"

#include <iostream>

using namespace std;

int main()
{
	/*u16 memSize = 0xFFFF;
	u8* mem = new u8[memSize + 1];

	CPU MOSCPU(mem, memSize);
	MOSCPU.LoadBinary("prog.bin", 0x0200);

	cout << hex << "Starting point: " << (int)MOSCPU.peek(MOSCPU.RESET_VECTOR + 1) << " " << (int)MOSCPU.peek(MOSCPU.RESET_VECTOR) << endl;

	MOSCPU.StartExecuting();

	cout << dec << "Result: " << (int)MOSCPU.peek(0x0a) << endl;

	delete[] mem;*/

	cout << "Hello!" << endl;
}

