#ifndef MEMORY_HPP
#define MEMORY_HPP

#include "TypeDef.hpp"
#include <cassert>

inline void ZeroMemory(void* ptr, u32 size)
{
    u8* p = static_cast<u8*>(ptr);
    for(u32 i = 0; i < size; i++)
    {
        p[i] = 0;
    }
}

inline void CopyMemory(void* dest, void* src, u32 size)
{
    u8* d = static_cast<u8*>(dest);
    u8* s = static_cast<u8*>(src);
    for(u32 i = 0; i < size; i++)
    {
        d[i] = s[i];
    }
}

inline usize AlignAddressForward(usize address, u8 alignment)
{
    const u8 mask = alignment - 1;
    assert((alignment & mask) == 0 && "Alignment is not a power of 2!");
    return (reinterpret_cast<usize>(address) + mask) & ~mask;
}

template<typename T>
inline void* AlignPointerForward(T* ptr, u8 alignment)
{
    const usize addr = reinterpret_cast<usize>(ptr);
    const usize alignedAddress = AlignAddressForward(addr, alignment);
    return reinterpret_cast<T*>(alignedAddress);
}

#endif