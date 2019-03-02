#define CATCH_CONFIG_MAIN

//Unit testing file.
#include <catch.hpp>

//Project files
#include "Array.h"


using namespace std;

TEST_CASE("Test length of a int*", "")
{
    uint dimension = 5;
    int* array = new int[dimension];

    uint result = Array::getSize(array);

    REQUIRE(dimension == result);

}