#pragma once

#include <iostream>
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

