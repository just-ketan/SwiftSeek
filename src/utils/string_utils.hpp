#pragma once
#include <string>
#include <algorithm>

namespace StringUtils{
    inline std::string tolower(std::string s){
        std::transform(s.begin(), s.end(), [](unsigned char c){ return std::tolower(c); });
        return s;
    }

    inline bool isAlnum(char c){
        return std::isalnum(static_cast<unsigned char>(c));
    }
}