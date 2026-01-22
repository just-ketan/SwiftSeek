#include "inverted_index.hpp"
#include "tokenizer.hpp"

#include <unordered_map>

void InvertedIndex::indexDocument(DocumentStore::DocId docId,
                                  std::string_view content) {
    auto tokens = Tokenizer::tokenize(content);

    std::unordered_map<std::string, uint32_t> termFreq;
    for (const auto& token : tokens) {
        ++termFreq[token];
    }

    for (const auto& [term, freq] : termFreq) {
        index_[term].push_back({docId, freq});
    }
}

bool InvertedIndex::containsTerm(std::string_view term) const {
    return index_.find(std::string(term)) != index_.end();
}

const InvertedIndex::PostingList*
InvertedIndex::getPostingList(std::string_view term) const {
    auto it = index_.find(std::string(term));
    if (it == index_.end()) {
        return nullptr;
    }
    return &it->second;
}

std::size_t InvertedIndex::vocabularySize() const noexcept {
    return index_.size();
}

void InvertedIndex::clear() {
    index_.clear();
}
