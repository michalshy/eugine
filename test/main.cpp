#include <catch2/catch_test_macros.hpp>
#include "core/alloc/StackAllocator.hpp"

StackAllocator stackAllocator(1024);

TEST_CASE( "Check stack allocator alignment", "[memory]" ) {
    void* ptr = stackAllocator.Alloc(33);
    printf("Address: %#0008llx\n", reinterpret_cast<usize>(ptr));
    REQUIRE( reinterpret_cast<usize>(ptr) % sizeof(usize) == 0 );
}