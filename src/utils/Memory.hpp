#ifndef MEMORY_HPP
#define MEMORY_HPP

#include "TypeDef.hpp"

static void ZeroMemory(void* ptr, u32 size)
{
    u8* p = static_cast<u8*>(ptr);
    for(u32 i = 0; i < size; i++)
    {
        p[i] = 0;
    }
}


#endif