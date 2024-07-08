#pragma once

#include "Global.h"

union Porv
{ // Pointer or value
    u8 *ptr;
    u64 val;
    Porv() : ptr(nullptr) {}
};