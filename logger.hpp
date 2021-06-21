#pragma once

#include <iostream>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <vector>


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
    void set_pattern(std::string format);
    
    template<typename T>
    void trace(const std::string& fmt){
        m_logger_message = log(TRACE, fmt);
        write();
    };

    template <typename Arg, typename... Args>
     void trace(const std::string& msg, Arg&& arg, Args&& ... args ){
        m_logger_message = log(TRACE, msg, std::forward<Arg>(arg),std::forward<Args>(args)...);
        write();
    };


    template <typename T>
    void fatal(const std::string& fmt){
        log(FATAL, fmt);
    };

private:
    template<typename T> 
    std::string to_string(const T& t){
        std::stringstream ss;
        ss << t;
        return ss.str();
    };

    // template <typename T>
    // void log(level_type lvl, const T &msg){
    //     if(lvl >= m_logger_level){

    //         auto now = std::chrono::system_clock::now();
    //         auto in_time_t = std::chrono::system_clock::to_time_t(now);
    //         m_time = std::localtime(&in_time_t);
    //         //m_datetime << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");

    //         switch (lvl)
    //         {
    //         case FATAL:
    //             m_message_level = "FATAL";
    //             break;
            
    //         case ERROR:
    //             m_message_level = "ERROR";
    //             break;
            
    //         case WARN:
    //             m_message_level = "WARN";
    //             break;
            
    //         case INFO:
    //             m_message_level = "INFO";
    //             break;

    //         case DEBUG:
    //             m_message_level = "DEBUG";
    //             break;        
    //         default:
    //             m_message_level = "TRACE";
    //             break;
    //         }

    //         m_logger_message = msg;

    //         write();
    //     }

    // };


    std::string log_impl(level_type lvl, const std::string& fmt, const std::vector<std::string>& strs)
    {
        static const char FORMAT_SYMBOL = '%';
        std::string res;
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
                        res += strs[num - 1];
                    else
                        res += FORMAT_SYMBOL + buf;
                    buf.clear();
                    if (ch != FORMAT_SYMBOL)
                    {
                        if (!last)
                            res += ch;
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
                        res += ch;
                }
            }
        }
        return res;
    }


    template<typename Arg, typename ... Args> 
    inline std::string log_impl(level_type lvl, const std::string& fmt, std::vector<std::string>& strs, Arg&& arg, Args&& ... args)
    {
        strs.push_back(to_string(std::forward<Arg>(arg)));
        return log_impl(lvl, fmt, strs, std::forward<Args>(args) ...);
    }

    inline std::string log(level_type lvl, const std::string& fmt)
    {
        return fmt;
    }

    template<typename Arg, typename ... Args> 
    inline std::string log(level_type lvl, const std::string& fmt, Arg&& arg, Args&& ... args)
    {
        std::vector<std::string> strs;
        return log_impl(lvl, fmt, strs, std::forward<Arg>(arg), std::forward<Args>(args) ...);
    }



    void write();
    void formating_message(size_t &pos );

    std::string m_logger_error;
    tm* m_time;
    level_type m_logger_level; 
    std::string m_message_level;
    std::string m_logger_message;

    std::ofstream m_of; // if chosed write in file
    std::ostream&  m_out;
    
    std::string m_logger_file_name;

    std::string m_format;

};