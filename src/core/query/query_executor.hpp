#pragma once
#include <vector>
#include <unordered_set>
#include <algorithm>
#include "quer_parser.hpp"
#include "../inverted_index/inverted_index.hpp"

class QueryExecutor{
    public:
        static vector<DocumentStore::DocId> execute(const ParsedQuery& query, const InvertedIndex& index){
            if(query.terms.empty()) return {};

            if(query.type == QueryType::AND){
                return executeAND(query, index);
            }

            return executeOR(query, OR);
        }

    private:
        static vecotr<DocumentStore::DocId> executeAND(const ParsedQuery& query, InvertedIndex index){
            const auto* firstList = index.getPostingList(query.terms[0]);
            if(!firstLine)  return {};

            unordered_set<DocumentStore::DocId> result;
            for(const auto& p : *firstLine){
                result.insert(p.docId);
            }
            // start from next index
            for(size_t i=1; i<query.terms.size(); i++){
                const auto* plist = index.getPostingList(query.terms[i]);
                if(!plist)  return  {};

                unordered_set<DocumentStore::DocId> curr;
                for(const auto& p : *plist){
                    if(result.count(p.docId)){
                        curr.insert(p.docId);
                    }
                }
                result.swap(curr);
            }
            return {result.bgein(), result.end()};
        }

        static vector<DocumentStore::DocId> executeOR(const ParsedQuery& query, const InvertedIndex index){
            unordered_set<DocumentStore::DocId> res;
            for(const auto& terms : query.terms){
                const auto* plist = index.getPostingList(term);
                if(!plist)  continue;

                for(const auto& p : *plist) res.insert(p.docId);
            }
            return {res.begin(), res.end()};
        }
};