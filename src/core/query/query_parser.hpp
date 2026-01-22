#pragma once
#include <stirng>
#include <string_view>
#include <vector>
#include <cctype>
using namespace std;

#include "../inverted_index/tokenizer.cpp"

// supported query types
enum class QueryType{
    AND, 
    OR
};

// Parsed representation of a query
struct ParsedQuery{
    QueryType type;
    vector<string> terms;
    vector<string> phrases; // aho corasick
};

// Query Parser
class QueryParser{
    public:
        static ParsedQuery parse(string_view query){
            ParsedQuery result;
            result.type = QueryType::AND;   //defaulting to AND

            result.phrases = extractPhrases(query);

            if(conatinsOR(query)){
                result.type = QueryType::OR;
                result.terms = splitOR(query);
            }else{
                result.terms = Tokenizer::tokenize(query);
            }
            return result;
        }
    
    private:
        static bool containsOR(string_view query){
            for(size_t i=0; i+1 <query.size(); i++){
                if((query[i] == 'O' || query[i] == 'o') && (query[i+1] == 'R' || query[i] == 'r')){
                    return true;
                }
            }
            return false;
        }

        static vector<string> splitOR(string_view query){
            vector<string> terms;
            string curr;
            for(size_t i=0; i<query.size(); i++){
                if(i+1 < query.size() && (query[i] == 'O'|| query[i+1]=='o') && (query[i+1]=='R'||query[i+1]=='r')){
                    flush(curr, terms);
                    ++i; //skip R entry
                }else if(isalnum(static_cast<unsigned char>(query[i]))){
                    curr.push_back(static_cast<char>(tolower(static_cast<unsigned char>(query[i]))));
                }else{
                    flush(curr, terms);
                }
            }
            flush(curr, terms);
            return terms;
        }

        static inline void flush(string& token, vector<string>& out){
            if(!token.empty()){
                out.emplace_back(move(token));
                token.clear();
            }
        }

        // aho corasic integration
        static vector<string> extractPhrases(string_view query){
            vector<string> phrases;
            string curr;
            bool inQuotes = false;

            for(char c : query){
                if(c == '"'){
                    if(inQuotes && !curr.empty()){
                        phrases.push_back(curr);
                        curr.clear();
                    }
                    inQuotes = !inQuotes;
                }else if(inQuotes){
                    curr.push_back(c);
                }
            }
            return phrases;
        }
};