#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "logger.hpp"


TEST_CASE( "multiple arguments" ) {
    
    Logger Log;
    std::vector<int> vec{1,2,3};

    Log.trace("HI %1", 1);
    Log.trace("HI %2", 1,"2");
} 
