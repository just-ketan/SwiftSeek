#pragma once
#include <cstdint>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>
using namespace std;
#include "../document/document_store.hpp"

// posting entry for a term, represents a document in which a term appears
struct Posting{
    DocumentStore::DocId docId;
    uint32_t termFrequency;
};

// inverted index mapping terms to posting lists
class InvertedIndex{
    public:
        using PostingList = vector<Posting>;

        // build index for a document
        void indexDocument(DocumentStore::DocId docId, string_view context);

        // check if a term exists in the index
        bool conatinsTerm(string_view term) const;

        // get Posting list for a term and return pointer to the same
        const PostingList* getPostingList(string_view term) const;

        //return number of unique indexed terms
        size_t vocabularySize() const noexcept;

        void clear();
    
    private:
        unordered_map<string, PostingList> index_;
};