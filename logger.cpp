#include "logger.hpp"

#include <vector>

#include <iostream>

Logger:: Logger()
: m_out( std::cout )
{ 
    m_logger_level = TRACE;
};

Logger:: Logger(const char* file_name) 
: m_of(file_name) 
, m_out( m_of )
{  
    if ( !m_of.good() ){
        std::cout << "error when opening";
    }
    else{
        m_logger_file_name = file_name;
        m_logger_level = TRACE;
    }
    
};

Logger:: ~Logger(){}

void Logger:: set_level(level_type level){
    m_logger_level = level;
};

void Logger:: write( ){
    m_out << m_logger_message.str();
    m_out << "\n";

};
