#include "query_executor.hpp"
#include "../../cache/lru_cache.hpp"
#include <string>

namespace{
    constexpr size_t QUERY_CACHE_CAPACITY = 1024;
    LRUCache<std::String, std::vector<DocumentStore::DocId>> queryCache(QUERY_CACHE_CAPACITY);
}

std::vector<DocumentStore::DocId> QueryExecuter::execute(const ParsedQuery& query, const InvertedIndex& index){
    if(query.terms.empty()) return {};

    std::string cacheKey;
    cacheKey.reserve(64);
    cacheKey += (query.type == QueryType::AND ? "AND:":"OR:");
    for(const auto& term : query.terms){
        cacheKey += term;
        cacheKey += ' ';
    }

    // check for cache hit
    if(queryCache.contains(cacheKey))   return queryCache.get(cacheKey);

    // check for cache miss
    std::vector<DocumentStore::DocId> res;
    if(query.type == QueryType::AND){
        res = executeAND(query, index);
    }else{
        res = executeOR(query, index);
    }

    
    queryCache.put(cacheKey, res);
    return res;
}