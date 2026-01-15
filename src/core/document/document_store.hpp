/* single source of truth
    maps {docid -> document contents}
    */

#pragma once
#include <cstdint>
#include <string>
#include <string_view>
#include<unordered_map>
#include <stdexception>
using namespace std;

class DocumentStore{
    public:
        using DocId = uint32_t;

        void addDocument(DocId docId, string content){
            documents_[docId] = move(content); 
        }
        
        bool contains(DocId docId) const {
            return documents_.find(docId) != documents.end();
        }

        string_view getDocument(DocId docId) const {
            auto it = documents_.find(docId);
            if(it == documets_.end()){
                throw out_of_range("Document ID not found");
            }
            return it->second;
        }

        size_t size() const noexcept{
            return documents_.size();
        }

        void clear(){
            documets_.clear()
        }
    private:
        unordered_map<DocId, string> documents_;
};