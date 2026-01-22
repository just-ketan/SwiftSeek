#pragma once
#include <string>
#include <vector>
#include <unordered_map>

class AhoCorasick{
    public:
        explicit AhoCorasick(const std::vector<std::string>& patterns);
        std::vector<int> match(const std::string& text) const;  // find all pattern matches in given string
    private:
        struct Node{
            std::unordered_map<char, int> next;
            int fail = -1;
            std::vector<int> output;
        };

        std::vector<Node> trie_;

        void buildTrie(const std::vector<std::string>& patterns);
        void buildFailureLinks();
};