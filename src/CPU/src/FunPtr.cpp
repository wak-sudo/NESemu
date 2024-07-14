#include "FunPtr.h"

#include <stdexcept>

void FunPtr::invoke(CPU *obj, Porv arg)
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

bool FunPtr::operator==(const FunPtr &other) const
{
    const FunTypes myType = this->type;
    if (myType != other.type)
        return false;

    switch (myType)
    {
    case VFZ:
        return this->zeroArg == other.zeroArg;
        break;
    case VFU8:
        return this->u8Arg == other.u8Arg;
        break;
    case VFPU8:
        return this->ptru8Arg == other.ptru8Arg;
        break;
    case VFU16:
        return this->u16Arg == other.u16Arg;
    default:
        throw std::runtime_error("FunPtr::invoke unimplemented branch.");
        break;
    }
}

size_t FunPtr::hash() const
{
    return std::hash<const void *>()(static_cast<const void *>(&zeroArg));
}