#pragma once

#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "../document/document_store.hpp"

struct Posting {
    DocumentStore::DocId docId;
    uint32_t termFrequency;
};

class InvertedIndex {
public:
    using PostingList = std::vector<Posting>;
    void indexDocument(DocumentStore::DocId docId, std::string_view content);
    bool containsTerm(std::string_view term) const;
    const PostingList* getPostingList(std::string_view term) const;
    std::size_t vocabularySize() const noexcept;
    void clear();

private:
    std::unordered_map<std::string, PostingList> index_;
};
