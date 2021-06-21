#pragma once

#include <iostream>
<<<<<<< HEAD
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
=======
#include <sstream>
#include <chrono>
#include <fstream>
#include <iomanip>

#include <list>
#include <map>
#include <set>
#include <vector>



template <class First, class Second>
std::stringstream& operator<<(std::stringstream& output, const std::pair<First, Second>& p);
template <class Iter>
std::stringstream& PrintSequence(std::stringstream& output, Iter begin, Iter end);
                     
template <class T1, class T2>                                  
inline std::stringstream& operator<<( std::stringstream& output,  const std::vector<T1, T2>& seq) { 
return PrintSequence(output, seq.begin(), seq.end() );           
}

template <class T1, class T2>                                  
inline std::stringstream& operator<<( std::stringstream& output,  const std::list<T1, T2>& seq) { 
return PrintSequence(output, seq.begin(), seq.end() );           
}
             
template <class T1, class T2, class T3>                            
inline std::stringstream& operator<<( std::stringstream& output, const std::set<T1, T2, T3>& seq) { 
return PrintSequence(output, seq.begin(), seq.end());               
}
                        
template <class T1, class T2, class T3, class T4>                      
inline std::stringstream& operator<<( std::stringstream& output, const std::map<T1, T2, T3, T4>& seq) { 
return PrintSequence(output, seq.begin(), seq.end());                   
}

template <class First, class Second>
inline std::stringstream& operator<<(std::stringstream& output,
                                const std::pair<First, Second>& p) {
  output << '(' << p.first << ", " << p.second << ')';
  return output;
}

template <typename T, size_t N>
inline std::stringstream& operator<<( std::stringstream& output,
                                const std::array<T, N>& seq) {
  return PrintSequence(output, seq.begin(), seq.end());
}

template <class Iter>
inline std::stringstream& PrintSequence( std::stringstream& output, Iter begin, Iter end) {
  output << '[';
  for (int i = 0; begin != end; ++i, ++begin) {
    if (i > 0) output << ", ";
    output << *begin;
  }
  if (begin != end) {
    output << " ...";
  }
  output << ']';
  return output;
}




class Logger{


    std::string m_date_and_time;
    std::string m_level;
    std::string m_message;
    
    std::stringstream m_datetime_level; // storage log
    std::stringstream m_msg;
    
    
    std::ofstream m_of; // if chosed write in file
    std::ostream&  m_out;
    
    std::string m_logger_file_name;

public:
    explicit Logger()
    : m_out( std::cout )
    { 
        m_logging_level = TRACE;
    };

    explicit Logger(std::string const log_name)
    : m_of(log_name) 
    , m_out( m_of )
    {  
        if ( !m_of.good() ){
            std::cout << "error when opening";
        }
        else{
            m_logger_file_name = log_name;
            m_logging_level = TRACE;
        }
        
    };

    ~Logger(){};
    
    template < typename Arg>
    void trace( Arg message){
        time_recording_and_level(TRACE);
        log(message);
        write(TRACE);
    };

    template < typename... Args>
    void trace( Args... message){
        time_recording_and_level(TRACE);
        log( message...);
        write(TRACE);
    };

    template < typename Arg>
    void trace(const char* msg, Arg message){        
        time_recording_and_level(TRACE);
        std::string str{msg};

        std::vector<size_t> positions; // holds all the positions that sub occurs within str

        size_t pos = str.find("%", 0);
        while(pos != std::string::npos)
        {
            positions.push_back(pos);
            pos = str.find("%",pos+1);
        }

        std::cout << "URA" << std::endl;
        m_msg.str("");
        
        log( message);
        write(TRACE);
    };

    // template < typename Arg>
    // void debug( Arg message){
    //     time_recording_and_level(DEBUG);
    //     log(message);
    //     write(DEBUG);
    // };

    // template < typename... Args>
    // void debug( Args... message){
    //     time_recording_and_level(DEBUG);
    //     log( message...);
    //     write(DEBUG);
    // };
    
    // template < typename Arg>
    // void info( Arg message){
    //     time_recording_and_level(INFO);
    //     log(message);
    //     write(INFO);
    // };

    // template < typename... Args>
    // void info( Args... message){
    //     time_recording_and_level(INFO);
    //     log( message...);
    //     write(INFO);
    // };

    // template < typename Arg>
    // void warn( Arg message){
    //     time_recording_and_level(WARN);
    //     log(message);
    //     write(WARN);
    // };

    // template < typename... Args>
    // void warn( Args... message){
    //     time_recording_and_level(WARN);
    //     log( message...);
    //     write(WARN);
    // };

    // template < typename Arg>
    // void error( Arg message){
    //     time_recording_and_level(ERROR);
    //     log(message);
    //     write(ERROR);
    // };

    // template < typename... Args>
    // void error( Args... message){
    //     time_recording_and_level(ERROR);
    //     log( message...);
    //     write(ERROR);
    // };
    
    // template < typename Arg>
    // void fatal( Arg message){
    //     time_recording_and_level(FATAL);
    //     log(message);
    //     write(FATAL);
    // };

    // template < typename... Args>
    // void fatal( Args... message){
    //     time_recording_and_level(FATAL);
    //     log( message...);
    //     write(FATAL);
    // };

    enum level_type {
        FATAL, ERROR, WARN, INFO, DEBUG, TRACE
    };

    void set_level(level_type level){
        m_logging_level = level;
    };

private:

    template < typename Arg>
    void log( Arg message){
        std::cout << message << std::endl;
        m_datetime_level << message << "\n";
    };

    template < typename Arg, typename... Args>
    void log(Arg message, Args... remainder_message){
        m_datetime_level << message ;
        log( remainder_message...);
    }
    
    void time_recording_and_level(level_type level);

    void current_time_and_date_in_m_datetime_level(){
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        m_datetime_level << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
        
    };  

    void write(level_type lvl);

    enum level_type m_logging_level; // storage level logging

};

>>>>>>> 313c421befdd7dc9e92e26aae85e5416413bcc32
