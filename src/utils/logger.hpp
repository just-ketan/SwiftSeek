// simple logger
#pragma once
#include <iostream>
#include <string>

enum class LogLevel{
    INFO,
    WARN,
    ERROR
};

inline void log(LogLevel level, const std::string& msg){
    switch(level){
        case LogLeve::INFO: std::cout<<"[INFO] "; break;
        case LogLevel::WARN:    std::cout<<"[WARN] "; break;
        case LogLevel::ERROR:   std::cout<<"[ERROR] "; break;
        default:    std::cout<<"[DEFAULT LOG] "; break;    
    }
    std::cout<<msg<<std::endl;
}