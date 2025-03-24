#ifndef STACKALLOCATOR_HPP
#define STACKALLOCATOR_HPP

#include "TypeDef.hpp"
#include "utils/Memory.hpp"

constexpr u32 kSTACK_ALLOCATOR_SIZE = 1024 * 1024;

class StackAllocator
{
    u8 memory[kSTACK_ALLOCATOR_SIZE];
    u32 marker;
    u32 markers[100];
    u32 markerIndex;
public:
    explicit StackAllocator() : marker(0), markerIndex(0){}
    void* Alloc(u32 size)
    {
        if(marker + size > kSTACK_ALLOCATOR_SIZE)
        {
            return nullptr;
        }
        void* ptr = memory + marker;
        markers[markerIndex++] = marker;
        marker += size;
        return ptr;
    }
    void Free()
    {
        ZeroMemory(memory + marker, marker - markers[markerIndex]);
        marker -= markers[markerIndex--];
    }
    void Clear()
    {
        ZeroMemory(memory, kSTACK_ALLOCATOR_SIZE);
        marker = 0;
    }
    ~StackAllocator(){}

private:

};

#endif