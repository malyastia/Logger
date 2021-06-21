#pragma once

#include <iostream>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>

#include <map> 


	/*std::for_each(vec2.begin(), vec2.end(), [](auto& n) { std::cout << n << " "; });
	*///std::cout << std::endl;
// template <class First, class Second>
// std::stringstream& operator<<(std::stringstream& output, const std::pair<First, Second>& p);
// template <class Iter>
// std::stringstream& PrintSequence(std::stringstream& output, Iter begin, Iter end);
                     
// template <class T1,class T2>                                  
// inline std::stringstream& operator<<( std::stringstream& output,  const std::vector<T1,  T2>& seq) { 
// return PrintSequence(output, seq.begin(), seq.end() );           
// }
                        
// template <class T1, class T2, class T3, class T4>                      
// inline std::stringstream& operator<<( std::stringstream& output, const std::map<T1, T2, T3, T4>& seq) { 
// return PrintSequence(output, seq.begin(), seq.end());                   
// }

// template <class First, class Second>
// inline std::stringstream& operator<<(std::stringstream& output,
//                                 const std::pair<First, Second>& p) {
//   output << '(' << p.first << ", " << p.second << ')';
//   return output;
// }

// template <typename T, size_t N>
// inline std::stringstream& operator<<( std::stringstream& output,
//                                 const std::array<T, N>& seq) {
//   return PrintSequence(output, seq.begin(), seq.end());
// }

// template <class Iter>
// inline std::stringstream& PrintSequence( std::stringstream& output, Iter begin, Iter end) {
//   output << '[';
//   for (int i = 0; begin != end; ++i, ++begin) {
//     if (i > 0) output << ", ";
//     output << *begin;
//   }
//   if (begin != end) {
//     output << " ...";
//   }
//   output << ']';
//   return output;
// }


class Logger{
public:
    explicit Logger();
    explicit Logger(const char* file_name);
    ~Logger();

    enum level_type{
        FATAL,
        ERROR,
        WARN,
        INFO,
        DEBUG,
        TRACE
    };

    void set_level(level_type level);
    
    void trace( const std::string& msg){
        m_logger_message.str("");
        log(msg);
        write();
    };

    template<typename Arg, typename ... Args> 
    void trace( const std::string& msg, Arg&& arg, Args&& ... args ){
        m_logger_message.str("");
        log( msg , std::forward<Arg>(arg), std::forward<Args>(args) ...);
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

    void write();

    std::string m_logger_error;
    tm* m_time;
    level_type m_logger_level; 
    std::string m_message_level;
    std::stringstream m_logger_message;

    std::ofstream m_of; // if chosed write in file
    std::ostream&  m_out;
    
    std::string m_logger_file_name;

};