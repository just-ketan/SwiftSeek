#pragma once
#include <vector>
#include <string>
#include "query_parser.hpp"
#include "../inverted_index/inverted_index.hpp"
#include "../document/document_store.hpp"

class QueryExecutor {
public:
    static std::vector<DocumentStore::DocId>
    execute(const ParsedQuery& query,
            const InvertedIndex& index,
            const DocumentStore& store);

private:
    static std::vector<DocumentStore::DocId>
    executeAND(const ParsedQuery& query, const InvertedIndex& index);

    static std::vector<DocumentStore::DocId>
    executeOR(const ParsedQuery& query, const InvertedIndex& index);
};
