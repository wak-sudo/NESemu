#pragma once

#include "Util.h"

class StackReg
{
    const u8 STACK_START_LOW = 0xFF;
    const u8 STACK_START_HIGH = 0x01;
    u8 reg;
    u8 *memory;
    StackReg(); // is unusable
public:
    StackReg(u8 *memoryPtr) : reg(STACK_START_LOW), memory(memoryPtr) {}
    u8 popStack();
    void pushStack(u8 val);
    u8 getVal() const;
    void setVal(u8 val);
    void reset();
    u16 getFullStackAdr() const;
};