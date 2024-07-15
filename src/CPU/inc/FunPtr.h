#pragma once

#include "Util.h"
#include "Porv.h"

#include <bitset> // for std::hash

class CPU; // forward declaration.

// Polimorphic type.
class FunPtr
{
    typedef void (CPU::*vFunZeroArg)();
    typedef void (CPU::*vFunOne8Arg)(u8 arg);
    typedef void (CPU::*vFunOne8Ptr)(u8 *arg);
    typedef void (CPU::*vFunOne16Arg)(u16 arg);

    // VFZ - Void funciton zero par
    // VFU8 - Void function param u8
    // VFPU8 - Void function param u8*
    // VFU16 - Void function param u16
    union
    {
        vFunZeroArg zeroArg;
        vFunOne8Arg u8Arg;
        vFunOne8Ptr ptru8Arg;
        vFunOne16Arg u16Arg;
        unsigned long hashTag;
    };

    enum FunTypes
    {
        EMPTY_PTR,
        VFZ,
        VFU8,
        VFPU8,
        VFU16
    } type;

public:
    FunPtr(vFunZeroArg ptr) : zeroArg(ptr), type(VFZ) {}
    FunPtr(vFunOne8Arg ptr) : u8Arg(ptr), type(VFU8) {}
    FunPtr(vFunOne8Ptr ptr) : ptru8Arg(ptr), type(VFPU8) {}
    FunPtr(vFunOne16Arg ptr) : u16Arg(ptr), type(VFU16) {}
    FunPtr() : hashTag(0), type(EMPTY_PTR) {}

    bool operator==(const FunPtr& other) const;
    FunPtr& operator=(const FunPtr& other);
    size_t hash() const;

    void invoke(CPU *obj, Porv arg);
};