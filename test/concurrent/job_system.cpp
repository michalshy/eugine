#include <catch2/catch_test_macros.hpp>
#include "TypeDef.hpp"
#include "concurrent/JobSystem.hpp"

JobSystem test();
TEST_CASE("Test Job system creation", "[concurrency]") {
    REQUIRE(1==1);
}