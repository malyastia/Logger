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

TEST_CASE( "Conteiner arguments" ) {
    
    Logger Log{"Conteiner"};
    std::vector<int> vec{1,2,3};
    Log.trace("vec %1", vec);

    std::deque<int> dque{4,5,6};
    Log.trace("dque %1", dque);

    std::list<int> lst{1,2,3};
    Log.trace("list %1", lst);

    std::forward_list<int> for_list{9,8,7};
    Log.trace("forward_list %1", for_list);
    
    std::stack<int> st;
    st.push(5);
    st.push(4);
    Log.trace("stack %1", st);

    std::queue<int> que;
    que.push(7);
    que.push(8);
    que.push(9);
    Log.trace("queue %1", que);

    std::map<int,int> mp{ {1,2}, {3,4}, {5,6} };
    Log.trace("map %1", mp);
    std::set<int> seet {1,2,3,4,5};
    Log.trace("set %1",seet);

    

} 

TEST_CASE( "Text formatting check" ) {
    
    Logger Log;
    //Log.set_level(Logger::FATAL);
    Log.trace("i%1", 1, 2);
    Log.trace("i", 1, 2);

}

TEST_CASE( "Changing the logging level" ) {
    
    Logger Log{};
    //Log.set_level(Logger::FATAL);
    Log.trace("i%1",50);
    Log.trace("i");

}

std::string randomize_message(){
    std::string str{"parameter string----"};

    int result =  10 + (rand() % 100);
    for(int i = 1; i < result; ++i ){
        str += "%" + std::to_string(i) + " ";
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

std::list<int> randomize_list(){
    std::list<int> lst;

    int result =  10 + (rand() % 100);
    for(int i = 1; i < result; ++i ){
        lst.push_back(10 + (rand() % 100));
    }
    return lst;
}

TEST_CASE("BENCHMARK"){
    auto start_time = std::chrono::system_clock::now();

    Logger log{"log.out"};

    for (size_t i = 0; i !=100000; ++i)
    {
        log.trace( randomize_message(), randomize_vec() );
        log.trace( randomize_message(), randomize_list() );        
    }

    auto finish_time = std::chrono::system_clock::now();
    double elapsed = std::chrono::duration<double>(finish_time - start_time).count();

    std::cout << "elapsed " << (elapsed/1) << " seconds" << std::endl;  
}