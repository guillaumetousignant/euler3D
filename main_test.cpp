 /*
 *  Created by Phil on 01/11/2010.
 *  Copyright 2010 Two Blue Cubes Ltd. All rights reserved.
 *
 *  Distributed under the Boost Software License, Version 1.0. (See accompanying
 *  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef TWOBLUECUBES_CATCH_WITH_MAIN_HPP_INCLUDED
#define TWOBLUECUBES_CATCH_WITH_MAIN_HPP_INCLUDED

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE( "stupid/1=2", "Prove that one equals 2" ){
    int one = 1;
    REQUIRE( one == 2 );
}


#endif // TWOBLUECUBES_CATCH_WITH_MAIN_HPP_INCLUDED
