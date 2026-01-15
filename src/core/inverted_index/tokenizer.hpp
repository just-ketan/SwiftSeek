// foundational tokenizer code
// FAST, DETERMINISTIC & ALLOCATION-EFFICIENT

#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <cctype>
using namespace std;

class Tokenizer{
    public:
        static vector<string> tokenize(string_view text){
            vector<string> tokens;
            tokens.reserve(32); // avoids small reallocs

            string current;
            current.reserve(16);

            for(char ch : text){
                if(isalnum(static_cast<unsigned char>(ch))) {
                    current.push_back(static_cast<char>(tolower(static_cast<unsigned char>(ch))));
                }else{
                    flushToken(current, tokens);
                }
            }

            flushToken(current, tokens);
            return tokens;
        }
    
    private:
        static inline void flushToken(string& current, vector<string>& tokens){
            if(!current.empty()){
                tokens.emplace_back(move(current));
                current.clear();
                current.reserve(16);
            }
        }
};