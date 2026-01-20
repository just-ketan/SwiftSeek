#include "document_store.hpp"

void DocumentStore::addDocument(DocId docId, std::string content) {
    documents_[docId] = std::move(content);
}

bool DocumentStore::contains(DocId docId) const {
    return documents_.find(docId) != documents_.end();
}

std::string_view DocumentStore::getDocument(DocId docId) const {
    auto it = documents_.find(docId);
    if (it == documents_.end()) {
        throw std::out_of_range("Document ID not found");
    }
    return it->second;
}

std::size_t DocumentStore::size() const noexcept {
    return documents_.size();
}

void DocumentStore::clear() {
    documents_.clear();
}
