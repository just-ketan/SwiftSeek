/* single source of truth
    maps {docid -> document contents}
    */

#pragma once
#include <cstdint>
#include <string>
#include <string_view>
#include<unordered_map>
#include <stdexcept>

class DocumentStore{
    public:
        using DocId = uint32_t;

        void addDocument(DocId docId, std::string content);
        bool contains(DocId docId) const;
        std::string_view getDocument(DocId docId) const;
        std::size_t size() const noexcept;
        void clear();

    private:
        std::unordered_map<DocId, std::string> documents_;
};