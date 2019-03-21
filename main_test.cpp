#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>

//Project files
#include "Metrics/test/head/TestMetricsInitializer.hpp"
#include "Metrics/test/head/TestIntegMetricsInitializer.hpp"

TEST_CASE( "stupid/1=1", "Prove that one equals 1" )
{
    int one = 1;
    REQUIRE( one == 1 );
}