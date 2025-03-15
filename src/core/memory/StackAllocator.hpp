#ifndef STACKALLOCATOR_HPP
#define STACKALLOCATOR_HPP

#include "TypeDef.hpp"

constexpr u32 kSTACK_ALLOCATOR_SIZE = 1024 * 1024;

class StackAllocator
{
    u8 m_memory[kSTACK_ALLOCATOR_SIZE];
    u32 m_marker;
    u32 m_markers[100];
    u32 m_markerIndex;
public:
    explicit StackAllocator() : m_marker(0), m_markerIndex(0){}
    void* alloc(u32 size)
    {
        if(m_marker + size > kSTACK_ALLOCATOR_SIZE)
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
        ZeroMemory(m_memory + m_marker, m_marker - m_markers[m_markerIndex]);
        m_marker -= m_markers[m_markerIndex--];
    }
    void clear()
    {
        ZeroMemory(m_memory, kSTACK_ALLOCATOR_SIZE);
        m_marker = 0;
    }
    ~StackAllocator(){}

private:

};

#endif