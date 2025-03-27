#ifndef MEMORYEXCEPTIONS_HPP
#define MEMORYEXCEPTIONS_HPP

#include <exception>

class AllocatorOutOfMemoryException : public std::exception {
    virtual const char* what() const noexcept override {
        return "Allocator out of memory exception: Not enough memory to allocate.";
    }    
};

#endif