// read from a batch file

#include "../core/query/query_parser.hpp"
#include "../core/query/query_executor.hpp"
#include "../utils/file_utils.hpp"
#include <iostream>

int main(){
    DocumentStore store;
    InvertedIndex index;

    store.addDocument(1, FileUtils::readFile("docs/sample.txt"));
    index.indexDocument(1, store.getDocument(1));

    std::cout<<"Indexed documents: "<<store.size() <<"\n";
}