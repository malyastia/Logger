#ifndef LOGGER
#define LOGGER

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

template<typename T, typename Alloc, template <typename, typename> class Container>
inline std::stringstream& operator<<( std::stringstream& output, const Container<T, Alloc> &sequence)
{
    output << '{';
    for (auto&& first : sequence) {
        output << " " << first ;
    }
    output << '}';
    return output;
}

template<typename T>
inline std::stringstream& operator<<( std::stringstream& output, const std::stack<T, std::deque<T>> &sequence)
{
    std::stack<T, std::deque<T>> st = sequence;
    output << '[';
    while( !st.empty()){
        output << " " << st.top();
        st.pop();
    }
    output << ']';
    return output;
}

template<typename T>
inline std::stringstream& operator<<( std::stringstream& output, const std::queue<T, std::deque<T>> &sequence)
{
    std::queue<T, std::deque<T>> que = sequence;
    output << '[';
    while( !que.empty()){
        output << " " << que.front();
        que.pop();
    }
    output << ']';
    return output;
}



class Logger{
public:
    explicit Logger():
    m_out( std::cout )
    , m_logger_level(TRACE)
    { };

    explicit Logger(const char* file_name)
    : m_of(file_name) 
    , m_out( m_of )
    , m_logger_level(TRACE)
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
        m_logger_level = level;
    };
    
    void trace( const std::string& msg){
        m_logger_message.str("");
        log(msg);
        write();
    };

    template<typename ... Args> 
    void trace( const std::string& msg, Args&& ... args ){
        m_logger_message.str("");
        log( msg, std::forward<Args>(args) ...);
        write();
    };

private:    
    template<typename T> 
    std::string to_string(const T& t)
    {
        std::stringstream ss;
        ss << t;
        return ss.str();
    }

    void log_impl(const std::string& fmt, const std::vector<std::string>& strs)
    {
        static const char FORMAT_SYMBOL = '%';
        std::stringstream res;
        std::string buf;
        bool arg = false;
        for (int i = 0; i <= static_cast<int>(fmt.size()); ++i)
        {
            bool last = i == static_cast<int>(fmt.size());
            char ch = fmt[i];
            if (arg)
            {
                if (ch >= '0' && ch <= '9')
                {
                    buf += ch;
                }
                else
                {
                    int num = 0;
                    if (!buf.empty() && buf.length() < 10)
                        num = atoi(buf.c_str());
                    if (num >= 1 && num <= static_cast<int>(strs.size()))
                        res << strs[num - 1];
                    else
                        res << FORMAT_SYMBOL + buf;
                    buf.clear();
                    if (ch != FORMAT_SYMBOL)
                    {
                        if (!last)
                            res << ch;
                        arg = false;
                    }
                }
            }
            else
            {
                if (ch == FORMAT_SYMBOL)
                {
                    arg = true;
                }
                else
                {
                    if (!last)
                        res << ch;
                }
            }
        }
        m_logger_message << res.str();
    }

    template<typename Arg, typename ... Args> 
    inline void log_impl(const std::string& fmt, std::vector<std::string>& strs, Arg&& arg, Args&& ... args)
    {
        strs.push_back(to_string(std::forward<Arg>(arg)));
        log_impl(fmt, strs, std::forward<Args>(args) ...);
    }

    inline void log(const std::string& fmt)
    {
        fmt;
    }

    template<typename Arg, typename ... Args> 
    inline void log(const std::string& fmt, Arg&& arg, Args&& ... args)
    {
        std::vector<std::string> strs;
        log_impl(fmt, strs, std::forward<Arg>(arg), std::forward<Args>(args) ...);
    }

    void write(){
        m_out << m_logger_message.str();
        m_out << "\n";

    };

    std::string m_logger_error;
    tm* m_time;
    level_type m_logger_level; 
    std::string m_message_level;
    std::stringstream m_logger_message;

    std::ofstream m_of; // if chosed write in file
    std::ostream&  m_out;
    
    std::string m_logger_file_name;

};

#endif