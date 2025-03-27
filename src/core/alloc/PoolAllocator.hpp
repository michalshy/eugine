#ifndef POOLALLOCATOR_HPP
#define POOLALLOCATOR_HPP

#include "TypeDef.hpp"
#include "exceptions/memory/MemoryExceptions.hpp"
#include <set>

/**
 * @brief Basic pool allocator with FIXED size
 * 
 * @tparam T Type of element to allocate 
 * TODO: Add dynamic resizing of pool allocator
 */

template <class T>
class PoolAllocator {
    usize chunksPerBlock;
    u8* memory;
    std::set<u8*> freeBlocks;
public:
    PoolAllocator(usize _chunksPerBlock) : chunksPerBlock(_chunksPerBlock) 
    {
        memory = new u8[sizeof(T) * chunksPerBlock];
        PushFreeBlocks();
    }
    void* Allocate() {
        if(freeBlocks.empty())
        {
            throw AllocatorOutOfMemoryException();
        }
        void* allocatedPlace = *freeBlocks.begin();
        freeBlocks.erase(freeBlocks.begin());
        return allocatedPlace;
    }
    void Deallocate(void* ptr) {
        freeBlocks.insert(reinterpret_cast<u8*>(ptr));
    }
    ~PoolAllocator() {
        delete [] memory;
    }
    void* GetMemory() { return memory; }
    usize GetChunkSize() { return sizeof(T); }
    usize GetChunksPerBlock() { return chunksPerBlock; }
protected:
    void PushFreeBlocks() {
        for(usize i = 0; i < chunksPerBlock; ++i)
        {
            freeBlocks.insert(memory + (i * sizeof(T)));
        }
    }
};

#endif