#include "FunPtr.h"

#include <stdexcept>

void FunPtr::invoke(CPU * obj, Porv arg)
{
    switch (type)
    {
    case VFZ:
        (obj->*zeroArg)();
        break;
    case VFU8:
        (obj->*u8Arg)((u8)arg.val);
        break;
    case VFPU8:
        (obj->*ptru8Arg)(arg.ptr);
        break;
    case VFU16:
        (obj->*u16Arg)((u16)arg.val);
    default:
        throw std::runtime_error("FunPtr::invoke unimplemented branch.");
        break;
    }
}