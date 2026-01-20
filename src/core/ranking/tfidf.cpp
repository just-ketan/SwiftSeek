// driver code that implements ranking logic

#include "tfidf.hpp"
#include <algorithm>
#include <unordered_map>
#include <cmath>

std::vector<TFIDFRanker::ScoreDocument> TFIDFRanker::rank(const std::vector<std::string>& queryTerms, const InvertedIndex& index, std::size_t totalDocuments){
    std::unordered_map<DocumentStore::DocId, double> scores;
    if(queryTerms.empty())  return {};

    for(const auto& term : queryTerms){
        const auto* postingList = index.getPostingList(term);
        if(!postingList)    continue;

        const std::size_t df = postingList->size();
        // IDF = log(totalDocs / (1 + df))
        const double idf = std::log(static_cast<double>(totalDocuments)/(1.0+static_cast<double>(df)));
        for(const auto& posting : *postingList){
            const double tf = static_cast<double>(posting.termFrequency);
            scores[posting.docId] += tf*idf;
        }
    }

    std::vector<ScoreDocument> ranked;
    ranked.reserve(scores.size());
    for(const auto& [docId, score] : scores){
        ranked.emplace_back(docId, score);
    }

    //sort
    std::sort(ranked.begin(), ranked.end(), [](const ScoreDocument& a, const ScoreDocument& b){ return a.second > b.second; });
    return ranked;
}
