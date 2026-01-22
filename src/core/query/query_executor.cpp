#include "query_executor.hpp"
#include "../../cache/lru_cache.hpp"
#include "../core/automata/aho_matcher.hpp"
#include <string>

namespace{
    constexpr size_t QUERY_CACHE_CAPACITY = 1024;
    LRUCache<std::String, std::vector<DocumentStore::DocId>> queryCache(QUERY_CACHE_CAPACITY);
}

std::vector<DocumentStore::DocId> QueryExecuter::execute(const ParsedQuery& query, const InvertedIndex& index){
    if(query.terms.empty() && query.phrases.empty()) return {};

    std::string cacheKey;
    cacheKey.reserve(64);
    cacheKey += (query.type == QueryType::AND ? "AND:":"OR:");
    for(auto& t : query.terms) cacheKey += t + " ";
    for(auto& p : query.phrases)    cacheKey += "\""+p+"\" ";

    // candidates generation
    std::vector<DocumentStore::DocId> candidates;
    if(query.type == QueryType::AND){
        candidates = executeAND(query, index);
    }else{
        candidates = executeOR(query, index);
    }

    // Aho-Corasick phase verification
    if(!query.phrases.empty()){
        AhoMatcher matcher(query.phrases);
        std::vector<DocumentStore::DocId> verified;
        for(auto docId : candidates){
            if(matcher.matches(docId, store))   verified.push_back(docId);
        }
        candidates.swap(verified);
    }
    
    queryCache.put(cacheKey, candidates);
    return candidates;
}