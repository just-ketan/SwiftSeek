#include "aho_corasick.hpp"
#include <queue>

AhoCorasick::AhoCorasick(const std::vector<std::string>& patterns) {
    trie_.push_back(Node{}); // root
    buildTrie(patterns);
    buildFailureLinks();
}

void AhoCorasick::buildTrie(const std::vector<std::string>& patterns) {
    for (std::size_t i = 0; i < patterns.size(); ++i) {
        int node = 0;
        for (char c : patterns[i]) {
            if (!trie_[node].next.count(c)) {
                trie_[node].next[c] = trie_.size();
                trie_.push_back(Node{});
            }
            node = trie_[node].next[c];
        }
        trie_[node].output.push_back(static_cast<int>(i));
    }
}

void AhoCorasick::buildFailureLinks() {
    std::queue<int> q;

    // Root must fail to itself
    trie_[0].fail = 0;

    // Initialize depth-1 nodes
    for (auto& [c, nxt] : trie_[0].next) {
        trie_[nxt].fail = 0;
        q.push(nxt);
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (auto& [c, nxt] : trie_[v].next) {
            int f = trie_[v].fail;

            // Walk failure links until we find a transition or hit root
            while (f != 0 && !trie_[f].next.count(c)) {
                f = trie_[f].fail;
            }

            if (trie_[f].next.count(c)) {
                trie_[nxt].fail = trie_[f].next[c];
            } else {
                trie_[nxt].fail = 0;
            }

            // Merge output links
            const auto& failOut = trie_[trie_[nxt].fail].output;
            trie_[nxt].output.insert(
                trie_[nxt].output.end(),
                failOut.begin(),
                failOut.end()
            );

            q.push(nxt);
        }
    }
}

std::vector<int> AhoCorasick::match(const std::string& text) const {
    std::vector<int> matches;
    int node = 0;

    for (char c : text) {
        while (node != 0 && !trie_[node].next.count(c)) {
            node = trie_[node].fail;
        }

        if (trie_[node].next.count(c)) {
            node = trie_[node].next.at(c);
        }

        for (int id : trie_[node].output) {
            matches.push_back(id);
        }
    }

    return matches;
}
