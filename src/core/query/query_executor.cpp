#include "query_executor.hpp"
#include "../automata/aho_matcher.hpp"
#include "../../cache/lru_cache.hpp"
#include <string>
#include <unordered_set>
#include <iostream>

namespace {
    constexpr std::size_t QUERY_CACHE_CAPACITY = 1024;
    LRUCache<std::string, std::vector<DocumentStore::DocId>> queryCache(QUERY_CACHE_CAPACITY);
}

std::vector<DocumentStore::DocId> QueryExecutor::execute(const ParsedQuery& query, const InvertedIndex& index, const DocumentStore& store) {
    if (query.terms.empty() && query.phrases.empty()) {
        return {};
    }

    // Build cache key
    std::string cacheKey;
    cacheKey += (query.type == QueryType::AND ? "AND:" : "OR:");
    for (const auto& t : query.terms)   cacheKey += t + " ";
    for (const auto& p : query.phrases) cacheKey += "\"" + p + "\" ";

    if (queryCache.contains(cacheKey)) {
        return queryCache.get(cacheKey);
    }

    // Candidate generation
    std::vector<DocumentStore::DocId> candidates;
    if (query.type == QueryType::AND) {
        candidates = executeAND(query, index);
    } else {
        candidates = executeOR(query, index);
    }

    // Phrase verification using Aho–Corasick
    if (!query.phrases.empty()) {
        AhoMatcher matcher(query.phrases);
        std::vector<DocumentStore::DocId> verified;

        for (auto docId : candidates) {
            if (matcher.matches(docId, store)) {
                verified.push_back(docId);
            }
        }
        candidates.swap(verified);
    }

    queryCache.put(cacheKey, candidates);
    return candidates;
}

std::vector<DocumentStore::DocId> QueryExecutor::executeAND(const ParsedQuery& query, const InvertedIndex& index) {
    std::cout << "ENTER executeAND\n";

    if (query.terms.empty()) return {};

    const auto* firstList = index.getPostingList(query.terms[0]);
    if (!firstList) return {};

    std::unordered_set<DocumentStore::DocId> result;
    for (const auto& p : *firstList) {
        result.insert(p.docId);
    }

    for (std::size_t i = 1; i < query.terms.size(); ++i) {
        std::cout << "AND term: " << query.terms[i] << "\n";
        const auto* plist = index.getPostingList(query.terms[i]);
        if (!plist) return {};

        std::unordered_set<DocumentStore::DocId> curr;
        for (const auto& p : *plist) {
            if (result.count(p.docId)) {
                curr.insert(p.docId);
            }
        }
        result.swap(curr);
    }
    return {result.begin(), result.end()};
}

std::vector<DocumentStore::DocId> QueryExecutor::executeOR(const ParsedQuery& query, const InvertedIndex& index) { 
    std::cout << "ENTER executeOR\n";
    std::unordered_set<DocumentStore::DocId> result;
    for (const auto& term : query.terms) {
        const auto* plist = index.getPostingList(term);
        if (!plist) continue;

        for (const auto& p : *plist) {
            result.insert(p.docId);
        }
    }
    return {result.begin(), result.end()};
}

