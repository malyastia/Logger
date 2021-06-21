#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "logger.hpp"

#include <string>


TEST_CASE( "multiple arguments" ) {
    
    Logger Log;
    Log.trace("HI %13","STR","STR","STR","STR","STR","STR","STR","STR","STR","STR","STR","9999","111");
} 
