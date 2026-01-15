#include "inverted_index.hpp"
#include "tokenizer.hpp"
#include <unordered_map>
using namespace std;

void InvertedIndex::indexDocument(DocumentStore::DocId docId, string_value content){
    auto tokens = Tokenizer::tokesize(content);

    unordered_map<string, uint32_t> termFreq;
    termFreq.reserve(tokens.size());

    // local term freq count
    for(const auto& token : tokens){
        ++termFreq[token];
    }

    //update inverted token
    for(auto& [term. freq] : termFreq){
        index_[term].push_back(Posting{docId, freq});
    }
}

bool InvertedIndex::containsTerm(string_view term) const{
    return index_.find(term) != index_.end();
}

const InvertedIndex::PostingList* InvertedIndex::getPostingList(string_view term) const {
    auto it = index_.find(string(term));
    if(it == index_.end()){
        return nullptr;
    }
    return &it->second;
} 

size_t InvertedIndex::vocabularySize() const {
    return index_.size();
}

void InvertedIndex::clear(){
    index_.clear();
}