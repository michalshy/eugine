#ifndef STACKALLOCATOR_HPP
#define STACKALLOCATOR_HPP

#include "TypeDef.hpp"

constexpr u32 STACK_ALLOCATOR_SIZE = 1024 * 1024;

class StackAllocator
{
    u32 size;
    u8 m_memory[STACK_ALLOCATOR_SIZE];
    u32 m_marker;
    u32 m_markers[100];
    u32 m_markerIndex;
public:
    explicit StackAllocator() : size(size), m_marker(0), m_markerIndex(0){}
    void* alloc(u32 size)
    {
        if(m_marker + size > STACK_ALLOCATOR_SIZE)
        {
            return nullptr;
        }
        void* ptr = m_memory + m_marker;
        m_markers[m_markerIndex++] = m_marker;
        m_marker += size;
        return ptr;
    }
    void free()
    {
        ZeroMemory(m_memory + m_marker, m_marker - m_markers[m_markerIndex--]);
        m_marker -= size;
    }
    ~StackAllocator(){}

private:

};

#endif