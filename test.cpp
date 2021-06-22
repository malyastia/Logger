#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "logger.hpp"

#include <list>
#include <forward_list>
#include <deque>

#include <queue>
#include <stack>
#include <set>
#include <map>


void con(std::string name){
    Logger Log{name};
    std::vector<int> vec{1,2,3};
    Log.trace("%1", vec);

    std::deque<int> dque{1,2,3};
    Log.trace("%1", dque);

    std::list<int> lst{1,2,3};
    Log.trace(" %1", lst);

    std::forward_list<int> for_list{1,2,3};
    Log.trace("%1", for_list);
    
    std::stack<int> st;
    st.push(3);
    st.push(2);
    st.push(1);
    Log.trace("%1", st);

    std::queue<int> que;
    que.push(1);
    que.push(2);
    que.push(3);
    Log.trace("%1", que);

    std::map<int,int> mp{ {1,2}, {3,4}, {5,6} };
    Log.trace("%1", mp);
    std::set<int> seet {1,2,3,4,5};
    Log.trace(" %1",seet);
}


std::vector<std::string> get_vector(std::string line) {
    std::vector<std::string> elements;
    std::stringstream ss(line);
    std::string q;
    int i=0;
    char chars[] = "{},[]";
    while (ss >> q ){ 
        for (unsigned int i = 0; i < strlen(chars); ++i)
        {
            q.erase (std::remove(q.begin(), q.end(), chars[i]), q.end());
        }
        if ( i > 1)
        elements.push_back(q);
    
    }
return elements;
}

TEST_CASE( "Container arguments" ) {
    
    std::string name = "Conteiner";
    con(name);
    

    std::ifstream myfile(name, std::ios::in);

    std::string line;

    if (myfile.is_open() ) {
        int i = 0;
        while ( std::getline(myfile, line) ) {
            std::string s;
            std::vector<std::string> str = get_vector(line);
            
            for(int j=0; j< str.size(); ++j ){
                CHECK( str.at(i) == std::to_string(i) );
            }
            ++i;

            if( i <= 7 ){
                break;
            }
            
        }
        myfile.close();
    }

} 

void write_log(std::string fname, Logger::level_type lvl){
    Logger logging(fname);
    
    logging.set_level(lvl);
    for (int i = 0; i < 5; i++) {
        logging.trace( "message");
        logging.debug( "message" );
        logging.info( "message" );
        logging.warn( "message" );
        logging.error( "message" );
        logging.fatal( "message" );
      }
}

void read_log(std::string fname, Logger::level_type lvl){

    std::ifstream myfile(fname, std::ios::in);
    std::string line,time, type, msg;
    
    if (myfile.is_open()) {
        int i = -1;
        std::string str {"message"};
        while ( std::getline(myfile, line) ) {
            std::stringstream ss(line);
            std::string s;
            ss >> time >> time >> type>>msg;
            
            if( type == "TRACE" && lvl>=5 ){
              ++i;
              REQUIRE( type + msg == std::string("TRACE") + str );
            }
            else if(type == "DEBUG" && lvl>=4){
              REQUIRE( type + msg == std::string("DEBUG") + str );
            }
            else if(type == "INFO" && lvl>=3){
              REQUIRE( type + msg == std::string("INFO") + str );
            }
            else if(type == "WARN" && lvl>=2){
              REQUIRE( type + msg == std::string("WARN") + str );
            }
            else if(type == "ERROR" && lvl>=1){
              REQUIRE( type + msg == std::string("ERROR") + str );
            }
            else if(type == "FATAL" && lvl>=0){
              REQUIRE( type + msg == std::string("FATAL") + str );
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

TEST_CASE( "Changing the logging level" ) {
    
    write_log("my.log",Logger::TRACE);
    read_log("my.log",Logger::TRACE);

    write_log("my1.log",Logger::DEBUG);
    read_log("my1.log",Logger::DEBUG);

    write_log("my2.log",Logger::INFO);
    read_log("my2.log",Logger::INFO);
    
    write_log("my2.log",Logger::WARN);
    read_log("my2.log",Logger::WARN);   

    write_log("my2.log",Logger::ERROR);
    read_log("my2.log",Logger::ERROR);   

    write_log("my2.log",Logger::FATAL);
    read_log("my2.log",Logger::FATAL);
}

std::string big_randomize_message(){
    std::string str{"parameter string---- "};

    int size = 1 + (rand() % 100);
    for(int i = 1; i < size; ++i ){
        str += "%" + std::to_string(1 + (rand() % 100)) + " ";
    }
    return str;
}


std::vector<int> place_arg;
std::string little_randomize_message(){
    std::string str{"parameter string---- "};
    place_arg.clear();
    int size = 1 + (rand() % 10);
    for(int i = 1; i <= size; ++i ){
        int number_arg = 1 + (rand() % 20);
        place_arg.push_back(number_arg);
        str += "%" + std::to_string(number_arg) + " ";
    }
    return str;
}

std::vector<int> randomize_vec(){
    std::vector<int> vec;

    int result =  10 + (rand() % 100);
    for(int i = 1; i < result; ++i ){
        vec.push_back(10 + (rand() % 100));
    }
    return vec;
}

std::stack<int> randomize_stack(){
    std::stack<int> lst;

    int result =  10 + (rand() % 100);
    for(int i = 1; i < result; ++i ){
        lst.push(10 + (rand() % 100));
    }
    return lst;
}

TEST_CASE("BENCHMARK"){
    auto start_time = std::chrono::system_clock::now();

    Logger log{"log.out"};

    for (size_t i = 0; i !=500000; ++i)
    {
        log.trace( big_randomize_message(), randomize_vec() );
        log.trace( big_randomize_message(), randomize_stack() );      
    }

    auto finish_time = std::chrono::system_clock::now();
    double elapsed = std::chrono::duration<double>(finish_time - start_time).count();

    //std::cout << "elapsed " << (elapsed/250000) << " seconds" << std::endl;  
    //elapsed 0.000132661 seconds
}