#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "logger.hpp"
#include <string>


TEST_CASE( "multiple arguments" ) {
    
    Logger Log;
    Log.trace("HI %2",1,"str");
} 
