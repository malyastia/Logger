#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "logger.hpp"

#include <string>

void write_log(std::string fname, Logger::level_type lvl){
    Logger logging(fname);
    
    logging.set_level(lvl);
    for (int i = 0; i < 5; i++) {
        logging.trace( i );
        // logging.debug( i );
        // logging.info( i );
        // logging.warn( i );
        // logging.error( i );
        // logging.fatal( i );
      }

}


void read_log(std::string fname, Logger::level_type lvl){

    std::ifstream myfile(fname, std::ios::in);
    std::string line,time, type, msg;
    
    if (myfile.is_open()) {
        int i = -1;
        while ( std::getline(myfile, line) ) {
            std::stringstream ss(line);
            std::string s;
            ss >> time >> time >> type>>msg;
            
            if( type == "TRACE" && lvl>=5 ){
              ++i;
              REQUIRE( type + msg == std::string("TRACE") + std::to_string(i));
            }
            else if(type == "DEBUG" && lvl>=4){
              REQUIRE( type + msg == std::string("DEBUG") + std::to_string(i));
            }
            else if(type == "INFO" && lvl>=3){
              REQUIRE( type + msg == std::string("INFO") + std::to_string(i));
            }
            else if(type == "WARN" && lvl>=2){
              REQUIRE( type + msg == std::string("WARN") + std::to_string(i));
            }
            else if(type == "ERROR" && lvl>=1){
              REQUIRE( type + msg == std::string("ERROR") + std::to_string(i));
            }
            else if(type == "FATAL" && lvl>=0){
              REQUIRE( type + msg == std::string("FATAL") + std::to_string(i));
            }          
            
        }
        if(i==0){
          std::cout << "FILE EMPTY";
        }
        myfile.close();
    }
    else {
      std::cout << "FILE NOT OPEN";
    }   

}

// TEST_CASE( "logging_level" ) {
    
//     write_log("my.log",Logger::TRACE);
//     read_log("my.log",Logger::TRACE);

//     write_log("my1.log",Logger::DEBUG);
//     read_log("my1.log",Logger::DEBUG);

//     write_log("my2.log",Logger::INFO);
//     read_log("my2.log",Logger::INFO);
    
//     write_log("my2.log",Logger::WARN);
//     read_log("my2.log",Logger::WARN);   

//     write_log("my2.log",Logger::ERROR);
//     read_log("my2.log",Logger::ERROR);   

//     write_log("my2.log",Logger::FATAL);
//     read_log("my2.log",Logger::FATAL);  
// } 

void write_multiplelog(std::string fname, Logger::level_type lvl){
    Logger logging(fname);
    
    logging.set_level(lvl);
    // for (int i = 0; i < 5; i++) {
    //     logging.trace( i,i,i );
    //   }
    logging.trace( "%s% ", "1");
    
    logging.trace("asd");
}

void read_multiplelog(std::string fname, Logger::level_type lvl){

    std::ifstream myfile(fname, std::ios::in);
    std::string line,time, type, msg;
    
    if (myfile.is_open()) {
        int i = 0;
        while ( std::getline(myfile, line) ) {
            line.erase(line.begin(),line.begin()+20);
            
            //REQUIRE( line == std::string("TRACE") + std::to_string(i)+std::to_string(i)+std::to_string(i));
            i++;
        }
        if(i==0){
          std::cout << "FILE EMPTY";
        }
        myfile.close();
    }
    else {
      std::cout << "FILE NOT OPEN";
    }   

}

TEST_CASE( "multiple arguments" ) {
    
    write_multiplelog("multiple.log",Logger::TRACE);
    read_multiplelog("multiple.log",Logger::TRACE);

} 


// TEST_CASE( "Conteiner" ) {
//     std::vector<int> vec{1, 2, 3};
//     std::list<int> lst{1, 2, 3};
//     std::map<std::string, int> mapp{{"foo", 1}, {"bar", 2}};
//     std::array<int, 3> arr{1, 2, 3};

//     Logger logging("conteiner");
//     logging.trace(vec);
//     logging.trace(lst);
//     logging.trace(mapp);
//     logging.trace(arr);
    
// }


// TEST_CASE("Benchmark_write_file") {
//     INFO("asdasd");
//     auto start_time = std::chrono::system_clock::now();
//     Logger log{"out.log"};

//     for (size_t i = 0; i != 40000; ++i)
//     {
//         log.trace("123456789");
//     }


//     auto finish_time = std::chrono::system_clock::now();
//     double elapsed = std::chrono::duration<double>(finish_time - start_time).count();
//     std::cout << "elapsed " << elapsed << " seconds" << std::endl;  
    
//     // 0.131699 seconds in file 

// }

// TEST_CASE("Foo") {
//     INFO("Test case start" << 42);
//     for (int i = 0; i < 2; ++i) {
//         INFO("The number is " << i);
//         CHECK(i == i);
//     }
// }
