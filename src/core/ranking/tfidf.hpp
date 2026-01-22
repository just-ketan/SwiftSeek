// TF-IDF Scoring interface
// gives score per document

#pragma once
#include <vector>
#include <unordered_map>
#include <cmath>
#include "../inverted_index/inverted_index.hpp"
#include "../document/document_store.hpp"

class TFIDFRanker{
    public:
        using ScoreDocument = std::pair<DocumentStore::DocId, double>;
        static std::vector<ScoreDocument> rank(const std::vector<std::string>& queryTerms, const InvertedIndex& index, std::size_t totalDocuments);
        // only thedefinition
};