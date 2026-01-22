#pragma once
#include "aho_corasick.hpp"
#include "../document/document_store.hpp"

class AhoMatcher{
    public:
        explicit AhoMatcher(const std::vector<std::string>& patterns) : automaton_(patterns) {}
        //check if any patterns appear in the document
        bool matches(DocumentStore::DocId docId, const DocumentStore& store) const {
            auto text = store.getDocument(docId);
            return !automaton_.match(std::string(text)).empty();
        }
    private:
        AhoCorasick automaton_;
};