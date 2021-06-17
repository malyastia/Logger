#include "logger.hpp"

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