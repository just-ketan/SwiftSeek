#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "core/document/document_store.hpp"
#include "core/inverted_index/inverted_index.hpp"
#include "core/query/query_parser.hpp"
#include "core/query/query_executor.hpp"
#include "core/ranking/tfidf.hpp"

int main() {
    std::cout << "==============================\n";
    std::cout << "       SwiftSeek Demo\n";
    std::cout << "==============================\n\n";

    // --------------------------------------------------
    // 1. Create document store and inverted index
    // --------------------------------------------------
    DocumentStore store;
    InvertedIndex index;

    std::cout << "[INFO] Adding documents...\n";

    store.addDocument(1, "high performance search engine in c plus plus");
    store.addDocument(2, "search engines use inverted index for fast lookup");
    store.addDocument(3, "aho corasick enables fast multi pattern matching");
    store.addDocument(4, "modern search engines combine ranking and indexing");

    // --------------------------------------------------
    // 2. Index all documents
    // --------------------------------------------------
    std::cout << "[INFO] Indexing documents...\n";

    for (DocumentStore::DocId id = 1; id <= store.size(); ++id) {
        index.indexDocument(id, store.getDocument(id));
    }

    std::cout << "[INFO] Indexed "
              << store.size()
              << " documents with vocabulary size = "
              << index.vocabularySize()
              << "\n\n";

    // --------------------------------------------------
    // 3. Run example queries
    // --------------------------------------------------
    std::vector<std::string> queries = {
        "search engine",
        "\"high performance\" search",
        "search AND engine",
        "aho OR engine"
    };

    for (const auto& q : queries) {
        std::cout << "----------------------------------\n";
        std::cout << "Query: " << q << "\n";

        // Parse query
        ParsedQuery parsed = QueryParser::parse(q);

        // Execute query (AND/OR + phrase filtering)
        auto candidates = QueryExecutor::execute(parsed, index, store);

        if (candidates.empty()) {
            std::cout << "No results found.\n";
            continue;
        }

        // Rank results using TF-IDF
        auto ranked = TFIDFRanker::rank(
            parsed.terms,
            index,
            store.size()
        );

        std::cout << "Results (ranked):\n";

        for (const auto& [docId, score] : ranked) {
            // Only show docs that survived filtering
            if (std::find(candidates.begin(), candidates.end(), docId)
                == candidates.end()) {
                continue;
            }

            std::cout << "  Doc " << docId
                      << " | score = " << score
                      << "\n      \""
                      << store.getDocument(docId)
                      << "\"\n";
        }
    }

    std::cout << "\n==============================\n";
    std::cout << "       Demo Completed\n";
    std::cout << "==============================\n";

    return 0;
}
