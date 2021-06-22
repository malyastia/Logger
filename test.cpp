#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "logger.hpp"

#include <list>
#include <forward_list>
#include <deque>

#include <queue>
#include <stack>
#include <set>

TEST_CASE( "multiple arguments" ) {
    
    Logger Log;
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
    
    // Log.trace("HI %2", 1,"2");
} 
