#ifndef STACKALLOCATOR_HPP
#define STACKALLOCATOR_HPP

#include "TypeDef.hpp"
#include "utils/Memory.hpp"

class StackAllocator
{
    u8* memory;
    u32 memorySize;
    void* marker;
public:
    explicit StackAllocator(u32 _memorySize) : memorySize(_memorySize) 
    {
        memory = new u8[memorySize];
        marker = AlignAddressForward(memory, sizeof(usize));
    }
    void* Alloc(u32 sizeToAlloc)
    {
        u32 currentSize = reinterpret_cast<u8*>(marker) - memory;
        if(currentSize + sizeToAlloc > memorySize)
        {
            memorySize *= 2;
            u8* newMemory = new u8[memorySize];
            CopyMemory(newMemory, memory, currentSize);
            delete[] memory;
            marker = AlignAddressForward(newMemory + currentSize, sizeof(usize));
            memory = newMemory;
        }
        void* allocedPlace = marker;
        marker = AlignAddressForward(reinterpret_cast<u8*>(marker) + sizeToAlloc, sizeof(usize));
        return allocedPlace;
    }
    void Free(void* ptr)
    {
        ZeroMemory(ptr, reinterpret_cast<u8*>(marker) - reinterpret_cast<u8*>(ptr));
        marker = ptr;
    }
    void Clear()
    {
        ZeroMemory(memory, memorySize);
        marker = 0;
    }
    ~StackAllocator(){}

private:

};

#endif