# SwiftSeek Architecture

## High-Level Architecture

[Query]
   |
[Parser]
   |
[Executor] ----> [LRU Cache]
   |
[Candidate Docs]
   |
[TF-IDF Ranker]
   |
[Results]

## Module Breakdown

- core/document → raw document storage
- core/inverted_index → term → posting lists
- core/query → parsing + execution
- core/ranking → relevance scoring
- cache → LRU caching
- benchmark / profiler → performance analysis

## Threading Model
Single-threaded by design for deterministic benchmarking.
