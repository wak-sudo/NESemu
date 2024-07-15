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
    static const u16 STACK_OFFSET = 0x0100;
    static const u16 STACK_MAX_SIZE = 0x100;
    StackReg(u8 *memoryPtr) : reg(STACK_START_LOW), memory(memoryPtr) {}
    u8 popStack();
    void pushStack(u8 val);
    u8 getVal() const;
    void setVal(u8 val);
    void reset();
    u16 getFullStackAdr() const;
};