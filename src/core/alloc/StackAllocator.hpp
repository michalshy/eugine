#ifndef STACKALLOCATOR_HPP
#define STACKALLOCATOR_HPP

#include "TypeDef.hpp"
#include "utils/Memory.hpp"
#include "exceptions/memory/MemoryExceptions.hpp"

/**
 * @brief Basic Stack Allocator with FIXED size
 * TODO: provide dynamic resizing
 */

class StackAllocator
{
    u8* memory;
    u32 memorySize;
    void* marker;
public:
    explicit StackAllocator(u32 _memorySize) : memorySize(_memorySize) 
    {
        memory = new u8[memorySize];
        marker = AlignPointerForward(memory, sizeof(usize));
    }
    void* Alloc(u32 sizeToAlloc)
    {
        u32 currentSize = reinterpret_cast<u8*>(marker) - memory;
        if(currentSize + sizeToAlloc > memorySize)
        {
            throw AllocatorOutOfMemoryException();
        }
        void* allocedPlace = marker;
        marker = AlignPointerForward(reinterpret_cast<u8*>(marker) + sizeToAlloc, sizeof(usize));
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
    void* GetMarker() { return marker; }
    u32 GetMemorySize() { return memorySize; }
    ~StackAllocator(){
        delete [] memory;
    }

private:

};

#endif