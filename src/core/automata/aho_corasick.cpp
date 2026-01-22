#include "aho_corasick.hpp"
#include <queue>

AhoCorasick::AhoCorasick(const std::vector<std::string>& patterns){
    trie_.push_back(Node{});    // root
    builTrie(patterns);
    buildFailureLinks();
}

void AhoCorasick::buildTrie(const std::vector<std::string>& patterns){
    for(int i=0; i<patterns.size(); i++){
        int node = 0;
        for(char c : patterns[i]){
            if(!trie_[node].next.count(c)){
                // if the charachter does not exist in trie branching
                trie_[node].next[c] = trie_.size();
                trie_.push_back(Node{});
            }
            node = trie_[node].next[c];
        }
        trie_[node].output.push_back(i);
    }
}

void AhoCorasick::buildFailureLinks(){
    std::queue<int> q;
    for(auto& [c,nxt] : trie_[0].next){
        trie_[nxt].fail = 0;
        q.push(nxt);
    }

    while(!q.empty()){
        int v = q.front(); q.pop();
        for(auto& [c,nxt] : trie[v].next){
            int f = trie_[v].fail;
            while(f!=-1 && !trie_[f].next.count(c)){
                f = trie_[f].fail;
            }
            trie_[nxt].fail = (f == -1) ? 0 : trie_[nxt].next[c];
            trie_[nxt].output.insert(trie_[nxt].output.end(), trie_[trie_[nxt].fail].output.begin(), trie_[trie_[nxt].fail].output.end());
            q.push(nxt);
        }
    }
}

std::vector<int> AhoCorasick::match(const std::string& text) const {
    std::vector<int> matches;
    int node = 0;
    for(char c : text){
        while(node && !trie_[node].next.count(c))   node = trie_[node].fail;
        if(trie_[node].next.count(c))   node = trie_[node].next.at(c);
        for(int id : trie_[node].output)    matches.push_back(id);
    }
    return matches;
}