#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>

//Project files
#include "Metrics/src/MetricsInitializer.h"
#include "Metrics/test/TestMetricsInitializer.hpp"

TEST_CASE( "stupid/1=1", "Prove that one equals 1" )
{
    int one = 1;
    REQUIRE( one == 1 );
}