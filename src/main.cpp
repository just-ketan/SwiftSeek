#include <iostream>

#include "core/document/document_store.hpp"
#include "core/inverted_index/inverted_index.hpp"
#include "core/query/query_parser.hpp"
#include "core/query/query_executor.hpp"

int main() {
    std::cout << "START\n";

    DocumentStore store;
    InvertedIndex index;

    std::cout << "ADDING DOCS\n";

    store.addDocument(1, "high performance search engine in c plus plus");
    store.addDocument(2, "search engines use inverted index");
    store.addDocument(3, "aho corasick enables fast multi pattern matching");

    std::cout << "INDEXING\n";

    for (DocumentStore::DocId id = 1; id <= 3; ++id) {
        index.indexDocument(id, store.getDocument(id));
    }

    std::cout << "PARSING QUERY\n";

    auto query = QueryParser::parse("\"high performance\" search");

    std::cout << "EXECUTING QUERY\n";

    auto results = QueryExecutor::execute(query, index, store);

    std::cout << "DONE\n";
}
