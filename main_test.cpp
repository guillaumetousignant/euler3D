#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>

TEST_CASE( "stupid/1=2", "Prove that one equals 2" ){
    std::cout << "This is the test main" << std::endl;
    int one = 1;
    REQUIRE( one == 2 );
}