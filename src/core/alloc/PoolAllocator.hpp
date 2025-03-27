#ifndef POOLALLOCATOR_HPP
#define POOLALLOCATOR_HPP

#include "TypeDef.hpp"

template<class T>
class PoolAllocator {
    u32 size;
    T* memory;
public:
    PoolAllocator<T>(u32 _size): size(_size) {
        memory = new T[size];
    }
    T* GetMemory(){ return memory; }
    ~PoolAllocator<T>(){
        delete [] memory;
    }
};

#endif