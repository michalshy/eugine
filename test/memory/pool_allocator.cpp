#include <catch2/catch_test_macros.hpp>
#include "core/alloc/PoolAllocator.hpp"

PoolAllocator<u32> pool(10);
TEST_CASE( "Check pool allocator", "[memory]" ) {
    u32* ptr = pool.GetMemory();
    REQUIRE( ptr != nullptr );
}

TEST_CASE("Check alignment by new", "[memory]") {
    u32* ptr = pool.GetMemory();
    REQUIRE( reinterpret_cast<usize>(ptr) % sizeof(usize) == 0 );
    REQUIRE( reinterpret_cast<usize>(ptr) % sizeof(usize)*2 == 0 );
}