#include <catch2/catch_test_macros.hpp>
#include "TypeDef.hpp"
#include "core/alloc/PoolAllocator.hpp"

/**
 * @brief 
 */
bool CheckAllocSize(void* base, void* el) {
    REQUIRE(reinterpret_cast<usize>(el) - reinterpret_cast<usize>(base) == sizeof(u32)*4 - sizeof(u32));
    return true;
}

PoolAllocator<u32> pool(4);
TEST_CASE( "Check pool allocator", "[memory]" ) {
    void* base = pool.GetMemory();
    void* el1 = pool.Allocate();
    void* el2 = pool.Allocate();
    void* el3 = pool.Allocate();
    void* el4 = pool.Allocate();
    // Check if is not nullptrs
    REQUIRE( el1 != nullptr );
    REQUIRE( el2 != nullptr );
    REQUIRE( el3 != nullptr );
    REQUIRE( el4 != nullptr );
    // Check distance
    REQUIRE(reinterpret_cast<usize>(el4) - reinterpret_cast<usize>(el3) == sizeof(u32));
    REQUIRE(reinterpret_cast<usize>(el3) - reinterpret_cast<usize>(el2) == sizeof(u32));
    REQUIRE(reinterpret_cast<usize>(el2) - reinterpret_cast<usize>(el1) == sizeof(u32));
    REQUIRE(reinterpret_cast<usize>(el1) - reinterpret_cast<usize>(base) == 0); // First element
    CheckAllocSize(base, el4);
    // Check exception
    REQUIRE_THROWS(pool.Allocate());
}

