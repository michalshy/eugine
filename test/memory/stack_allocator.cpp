#include <catch2/catch_test_macros.hpp>
#include "core/alloc/StackAllocator.hpp"


/**
 * @brief Basic aligment check 
 */
StackAllocator stackAlign(1024);
TEST_CASE( "Check stack allocator alignment", "[memory]" ) {
    void* ptr = stackAlign.Alloc(33);
    REQUIRE( reinterpret_cast<usize>(ptr) % sizeof(usize) == 0 );
    ptr = stackAlign.Alloc(33);
    REQUIRE( reinterpret_cast<usize>(ptr) % sizeof(usize) == 0 );
    ptr = stackAlign.Alloc(1);
    REQUIRE( reinterpret_cast<usize>(ptr) % sizeof(usize) == 0 );
    ptr = stackAlign.Alloc(0);
    REQUIRE( reinterpret_cast<usize>(ptr) % sizeof(usize) == 0 );
}

/**
 * @brief Size manipulation 
 */
StackAllocator stackResize(8);
TEST_CASE("Check exception", "[memory]") {
    REQUIRE_THROWS(stackResize.Alloc(9));
}
TEST_CASE("Check freeing of stack allocator", "[memory]") {
    void* ptr = stackResize.Alloc(8);
    stackResize.Free(ptr);
    REQUIRE(stackResize.GetMarker() == ptr);
}
TEST_CASE("Check zero allocation", "[memory]") {
    void* ptr = stackResize.Alloc(0);
    REQUIRE(stackResize.GetMarker() == ptr);
}
