#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace FileUtils{
    inline std::string readFile(const std::string& path){
        std::ifstream file(path);
        if(!file.is_open()) throw std::runtime_error("Failed to open file from: ", path);
        std::ostringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }
}