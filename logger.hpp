#pragma once

#include <iostream>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>

#include <vector>

#include <deque>
#include <stack>
#include <queue>

// vector list forward_list deque
template<class T, class Alloc, template <class, class> class Container>
inline std::stringstream& operator<<( std::stringstream& output, const Container<T, Alloc> &sequence)
{
    auto _iter = output.tellp();
    for (const auto & elem : sequence) {
        output << ( output.tellp() != _iter ? ", ": "{") << elem ;
    }
    output << '}';
    return output;
}

template<class T>
inline std::stringstream& operator<<( std::stringstream& output, const std::stack<T, std::deque<T>> &sequence)
{
    std::stack<T, std::deque<T>> st = sequence;  
    auto _iter = output.tellp();
    while( !st.empty()){
        output << ( output.tellp() != _iter ? ", ": "{") << st.top();
        st.pop();
    }
    output <<  '}';
    return output;
}

template<class T>
inline std::stringstream& operator<<( std::stringstream& output, const std::queue<T, std::deque<T>> &sequence)
{
    std::queue<T, std::deque<T>> que = sequence;
    auto _iter = output.tellp();
    while( !que.empty()){
        output << ( output.tellp() != _iter ? ", ": "{") << que.front();
        que.pop();
    }
    output << '}';
    return output;
}
//map
template <typename Key, typename T, typename Compare = std::less<Key>, 
    typename Alloc = std::allocator<std::pair<const Key, T> > >
inline std::stringstream& operator<<( std::stringstream& output, const std::map<Key, T, Compare, Alloc> &sequence)
{
    auto _iter = output.tellp();  
    for (const auto& kv : sequence) {
        output << ( output.tellp() != _iter ? ", ": "{") << "[" << kv.first << " - " << kv.second << "]" ;
    }
    output << '}';
    return output;
}

//set
template<typename Key, typename Compare = std::less<Key>,
	typename Alloc = std::allocator<Key> >
inline std::stringstream& operator<<( std::stringstream& output, const std::set<Key, Compare, Alloc> &sequence)
{
    auto _iter = output.tellp();
    for(const auto& elem : sequence) {
        output << ( output.tellp() != _iter ? ", ": "{")  << elem ;
    } 
    output << '}';
    return output;
}

class Logger{
public:
    explicit Logger():
    m_out( std::cout )
    , m_logging_level(TRACE)
    { };

    explicit Logger(std::string file_name)
    : m_of(file_name) 
    , m_out( m_of )
    , m_logging_level(TRACE)
    , m_logger_file_name( file_name)
    { };

    ~Logger(){};

    enum level_type{
        FATAL,
        ERROR,
        WARN,
        INFO,
        DEBUG,
        TRACE
    };

    void set_level(const level_type level){
        m_logging_level = level;
    };
    
    void trace( const std::string& msg){
        if(m_logging_level >= TRACE){
            m_message_level = "TRACE";
            current_time_and_date_in_log_lines();
            m_message.str("");
            log(msg);
            write();
        }
    };

    template<typename ... Args> 
    void trace( const std::string& msg, const Args& ... args ){
        if(m_logging_level >= TRACE){
            current_time_and_date_in_log_lines();
            m_message_level = "TRACE";
            m_message.str("");
            log( msg, (args) ...);
            write();
        }
    };

    void debug( const std::string& msg){
        if(m_logging_level >= DEBUG){
            m_message_level = "DEBUG";
            current_time_and_date_in_log_lines();
            m_message.str("");
            log(msg);
            write();
        }
    };

    template<typename ... Args> 
    void debug( const std::string& msg, const Args& ... args ){
        if(m_logging_level >= DEBUG){
            current_time_and_date_in_log_lines();
            m_message_level = "DEBUG";
            m_message.str("");
            log( msg, (args) ...);
            write();
        }
    };

    void info( const std::string& msg){
        if(m_logging_level >= INFO){
            m_message_level = "INFO";
            current_time_and_date_in_log_lines();
            m_message.str("");
            log(msg);
            write();
        }
    };

    template<typename ... Args> 
    void info( const std::string& msg, const Args& ... args ){
        if(m_logging_level >= INFO){
            current_time_and_date_in_log_lines();
            m_message_level = "INFO";
            m_message.str("");
            log( msg, (args) ...);
            write();
        }
    };

    void warn( const std::string& msg){
        if(m_logging_level >= WARN){
            m_message_level = "WARN";
            current_time_and_date_in_log_lines();
            m_message.str("");
            log(msg);
            write();
        }
    };

    template<typename ... Args> 
    void warn( const std::string& msg, const Args& ... args ){
        if(m_logging_level >= WARN){
            current_time_and_date_in_log_lines();
            m_message_level = "WARN";
            m_message.str("");
            log( msg, (args) ...);
            write();
        }
    };

    void error( const std::string& msg){
        if(m_logging_level >= ERROR){
            m_message_level = "ERROR";
            current_time_and_date_in_log_lines();
            m_message.str("");
            log(msg);
            write();
        }
    };

    template<typename ... Args> 
    void error( const std::string& msg, const Args& ... args ){
        if(m_logging_level >= ERROR){
            current_time_and_date_in_log_lines();
            m_message_level = "ERROR";
            m_message.str("");
            log( msg, (args) ...);
            write();
        }
    };

    void fatal( const std::string& msg){
        if(m_logging_level >= FATAL){
            m_message_level = "FATAL";
            current_time_and_date_in_log_lines();
            m_message.str("");
            log(msg);
            write();
        }
    };

    template<typename ... Args> 
    void fatal( const std::string& msg, const Args& ... args ){
        if(m_logging_level >= FATAL){
            current_time_and_date_in_log_lines();
            m_message_level = "FATAL";
            m_message.str("");
            log( msg, (args) ...);
            write();
        }
    };

private:    
    template<typename T> 
    std::string to_string(const T& t)
    {
        std::stringstream ss;
        ss << t;
        return ss.str();
    }

    void log_impl(const std::string& str, const std::vector<std::string>& strs)
    {
        static const char FORMAT_SYMBOL = '%';
        std::stringstream res;
        std::string number_argument;
        bool arg = false;
        int size_str = static_cast<int>(str.size());
        for (int i = 0; i <= size_str; ++i)
        {
            bool last = i == size_str;
            char ch = str[i];
            if (!arg && ch == FORMAT_SYMBOL) {
                    arg = true;
                }
            else if(!arg && ch != FORMAT_SYMBOL) {
                if (!last)
                    res << ch;
            }
            else if ( arg && (ch >= '0' && ch <= '9') ) {
                number_argument += ch;
            }
            else {
                int num = 0;
                if (!number_argument.empty() && number_argument.length() < 10)
                    num = atoi(number_argument.c_str());
                if (num >= 1 && num <= static_cast<int>(strs.size()))
                    res << strs[num - 1];
                else
                    res << FORMAT_SYMBOL + number_argument;
                number_argument.clear();
                if (ch != FORMAT_SYMBOL)
                {
                    if (!last)
                        res << ch;
                    arg = false;
                }
            }
            
        }
        m_message << res.str();
    }

    template<typename Arg, typename ... Args> 
    inline void log_impl(const std::string& str, std::vector<std::string>& strs, const Arg& arg,const Args& ... args)
    {
        strs.push_back(to_string((arg)));
        log_impl(str, strs, (args) ...);
    }

    inline void log(const std::string& str)
    {
        m_message << str;
    }

    template<typename Arg, typename ... Args> 
    inline void log(const std::string& str, const Arg& arg, const Args& ... args)
    {
        std::vector<std::string> strs;
        log_impl(str, strs, (arg), (args) ...);
    }

    void current_time_and_date_in_log_lines(){
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        m_time = std::localtime(&in_time_t);
        
    };

    void write(){
        m_out << std::put_time(m_time, "%Y-%m-%d %X") << "  " << m_message_level;
        for(int i = m_message_level.size(); i <= 8; ++i){
            m_out << " ";
        }
        m_out << m_message.str()<< "  ";
        m_out << "\n";

    };

    tm* m_time;
    level_type m_logging_level; 
    std::string m_message_level;
    std::stringstream m_message; // storage for message

    std::ofstream m_of; // if chosed write in file
    std::ostream&  m_out; // stream for write file or console
    
    std::string m_logger_file_name;

};
