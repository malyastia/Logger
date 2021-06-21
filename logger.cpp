#include "logger.hpp"

<<<<<<< HEAD
#include <vector>

#include <iostream>

Logger:: Logger()
: m_out( std::cout )
{ 
    m_logger_level = TRACE;
    m_format = "[%d-%m-%Y %H:%M:%S] [%l] %v";
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
        m_format = "[%d-%m-%Y %H:%M:%S] [%l] %v";
    }
    
};

Logger:: ~Logger(){}

void Logger:: set_level(level_type level){
    m_logger_level = level;
};

void Logger::set_pattern(std::string format){
    std::cout << "URA";
};




/*
%% 	The % sign 	"%"
%+ 	spdlog's default format 

%m month
%a Abbreviated weekday name
%A 	Full weekday name
%b 	Abbreviated month name 	"Aug"
%B 	Full month name 	"August"
%c 	Date and time representation 	"Fri Jun 18 16:46:41 2021 "
%C 	Year in 2 digits 	"14"
%Y 	Year in 4 digits 	"2014"
%D or %x 	Short MM/DD/YY date 	"08/23/14"
%m 	Month 01-12 	"11"
%d 	Day of month 01-31 	"29"
%H 	Hours in 24 format 00-23 	"23"
%I 	Hours in 12 format 01-12 	"11"
%M 	Minutes 00-59 	"59"
%S 	Seconds 00-59 	"58"
%p 	AM/PM 	"AM"
%r 	12 hour clock 	"02:55:02 pm"
%R 	24-hour HH:MM time, equivalent to %H:%M 	"23:55"

%l log level
%L short log level 
%v message

*/

void Logger:: write( ){
    if ( m_format.size() != std::string::npos ){

        m_out << m_logger_message;

        // std::string message{m_format};

        // std::vector<size_t> pos_;

        // size_t pos = m_format.find("%");
        // m_format.replace( m_format.find("%v"), m_format.find("%") +  m_message_level.size(), m_message_level );
        

        // while( pos != std::string::npos ){

        //     formating_message(pos);

        //     // size_t position = m_format.find("");
        //     // if( )
        //     // positions_opening_brace.push_back( pos_opening_brace);
        //     // pos_opening_brace = m_format.find( "{", pos_opening_brace + 1);
        // }

        /*

        m_out << m_logger_error;
        m_out << std::put_time(m_time, "[%H:%M:%S]") ;
        m_out << m_message_level;
        m_out << m_logger_message;

        */

    }
    m_out << "\n";

};

void Logger:: formating_message(size_t &pos ){

    char elem = m_format.at(pos);
    switch (elem)
    {
    case 'a':
        break;
    
    default:
        break;
    }

    
};


    // std::vector<size_t> positions_opening_brace;
    // std::vector<size_t> positions_closing_brace;

    // size_t pos_opening_brace = m_format.find("{", 0);
    // size_t pos_closing_brace = m_format.find("}", 0);

    // if( pos_opening_brace != std::string::npos && pos_closing_brace == std::string::npos ){
    //     // std::cout << "invalid format string";
    //     m_logger_message = "unmatched '}' in format s";
    //     m_logger_error = "*** LOG ERROR ***";
    // }
    // else if( pos_opening_brace < pos_closing_brace ){   
    //     while(pos_opening_brace != std::string::npos){
    //         positions_opening_brace.push_back( pos_opening_brace);
    //         pos_opening_brace = m_format.find( "{", pos_opening_brace + 1);
    //     }

    //     while(pos_closing_brace != std::string::npos){
    //         positions_opening_brace.push_back( pos_opening_brace);
    //         pos_closing_brace = m_format.find("}", pos_closing_brace + 1);
    //     }

    //     if( positions_opening_brace.size() != positions_closing_brace.size() ){
    //         // std::cout << "unmatched '}' in format string";
    //         m_logger_message = "unmatched '}' in format string";
    //         m_logger_error = "*** LOG ERROR ***";
    //     }
    //     else{
    //         m_format.replace(positions_opening_brace.at(0),positions_opening_brace.at(0) + std::string("hidfs").size(),  "hidfs");
    //         std::cout << "format" << m_format << std::endl;
    //     }
    // }
=======
void Logger:: write(level_type lvl){
    if( m_logging_level >= lvl){
        m_out << m_datetime_level.str();
        m_datetime_level.str("");
    }else{
        m_datetime_level.str("");
    }
};

void  Logger:: time_recording_and_level(level_type level){
    
    current_time_and_date_in_m_datetime_level();
    m_datetime_level << " ";
    switch (level)
    {
    case INFO:
        m_datetime_level << "INFO";
        break;
    case DEBUG:
        m_datetime_level << "DEBUG";
        break;
    case WARN: 
        m_datetime_level << "WARN";
        break;
    case ERROR:
        m_datetime_level << "ERROR";
        break;
    case TRACE:
        m_datetime_level << "TRACE";
        break;
    default:
        m_datetime_level << "FATAL";
        break;
    }
};
>>>>>>> 313c421befdd7dc9e92e26aae85e5416413bcc32
