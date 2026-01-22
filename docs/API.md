# SwiftSeek – Public API Documentation

This document describes the **public-facing C++ APIs** exposed by SwiftSeek.
It is intended for developers who want to:
- understand how the engine works
- integrate SwiftSeek into another application
- extend or modify its components

---

## 📦 Core Components

### 1. DocumentStore

Stores raw document contents and acts as the **single source of truth**.

```cpp
class DocumentStore {
public:
    using DocId = uint32_t;

    void addDocument(DocId id, std::string content);
    bool contains(DocId id) const;
    std::string_view getDocument(DocId id) const;
    std::size_t size() const noexcept;
    void clear();
};
```

Responsibilities
    - Owns document text
    - Provides immutable access during indexing and querying
    - No indexing logic inside this class

2. InvertedIndex

Maps terms to posting lists for fast retrieval.
```cpp
class InvertedIndex {
public:
    void indexDocument(DocumentStore::DocId id,
                       std::string_view content);

    const PostingList* getPostingList(std::string_view term) const;
    bool containsTerm(std::string_view term) const;
    std::size_t vocabularySize() const noexcept;
    void clear();
};
```
```cpp
PostingList structure

struct Posting {
    DocId docId;
    uint32_t termFrequency;
};
```

3. QueryParser

Parses raw query strings into a structured representation.
```cpp
ParsedQuery QueryParser::parse(std::string_view query);
```

Supports
    - AND / OR queries
    - Phrase queries using quotes
    - Token normalization

4. QueryExecutor

Executes parsed queries against the index and document store.
```cpp
std::vector<DocumentStore::DocId>
QueryExecutor::execute(const ParsedQuery& query,
                       const InvertedIndex& index,
                       const DocumentStore& store);
```

Pipeline
|-Candidate retrieval (inverted index)
|
|-Phrase verification (Aho–Corasick)
|
|-Result caching (LRU)


5. TFIDFRanker
Ranks documents based on relevance.
```cpp
std::vector<ScoreDocument>
TFIDFRanker::rank(const std::vector<std::string>& terms,
                  const InvertedIndex& index,
                  std::size_t totalDocuments);
```

🔒 Thread Safety

Current version is single-threaded
All APIs assume external synchronization if used concurrently


🚧 Stability Guarantees
APIs are stable within a major version
Internal implementation may change without breaking public interfaces
