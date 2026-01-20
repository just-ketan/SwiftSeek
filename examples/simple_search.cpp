#include "../core/query/query_parse.hpp"
#include "../core/query/query_executor.hpp"
#include "../core/inverted_index/inverted_index.hpp"
#include "../core/documet/document_store.hpp"
#include <iostream>

int main(){
    DocumentStore store;
    InvertedIndex index;

    store.addDocument(1, "high performance search engine");
    store.addDocument(2, "search engines use inverted index");

    index.indexDocument(1, store.getDocument(1));
    index.indexDocument(2, store.getDocument(2));

    auto parsed = QueryParser::parse("search engine");
    auto res = QueryExecutor::execute(parsed, index);

    for(auto id : res)  std::cout<<"Found doc: "<<id<< "\n";
}