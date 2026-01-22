#pragma once
#include <vector>
#include <unordered_set>
#include <algorithm>
#include "query_parser.hpp"
#include "../inverted_index/inverted_index.hpp"
#include "../document/document_store.hpp"
#include "../core/automata/aho_matcher.hpp"

class QueryExecuter{
    public:
        static std::vector<DocumentStore::DocId> execute(const ParsedQuery& query, const InvertedIndex& index){
            if(query.terms.empty()) return {};

            if(query.type == QueryType::AND){
                return executeAND(query, index);
            }

            return executeOR(query, index);
        }

    private:
        static std::vector<DocumentStore::DocId> executeAND(const ParsedQuery& query, const InvertedIndex& index){
            const auto* firstLine = index.getPostingList(query.terms[0]);
            if(!firstLine)  return {};

            std::unordered_set<DocumentStore::DocId> result;
            for(const auto& p : *firstLine){
                result.insert(p.docId);
            }
            // start from next index
            for(std::size_t i=1; i<query.terms.size(); i++){
                const auto* plist = index.getPostingList(query.terms[i]);
                if(!plist)  return  {};

                std::unordered_set<DocumentStore::DocId> curr;
                for(const auto& p : *plist){
                    if(result.count(p.docId)){
                        curr.insert(p.docId);
                    }
                }
                result.swap(curr);
            }
            return {result.begin(), result.end()};
        }

        static std::vector<DocumentStore::DocId> executeOR(const ParsedQuery& query, const InvertedIndex& index){
            std::unordered_set<DocumentStore::DocId> res;
            for(const auto& term : query.terms){
                const auto* plist = index.getPostingList(term);
                if(!plist)  continue;

                for(const auto& p : *plist) res.insert(p.docId);
            }
            return {res.begin(), res.end()};
        }
};