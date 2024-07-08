#include "Util.h"

u16 Util::mergeBytes(u8 low, u8 high)
{
    return ((u16)high << 8) + low;
}