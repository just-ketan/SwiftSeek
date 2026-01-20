# SwiftSeek – Design Document

## Overview
SwiftSeek is a high-performance, single-node search engine implemented fully in C++.
It is designed to demonstrate algorithmic optimization, clean architecture, and
measurable performance improvements.

## Core Pipeline
1. Document ingestion
2. Tokenization
3. Inverted index construction
4. Query parsing
5. AND / OR execution
6. TF-IDF ranking
7. LRU caching of results

## Key Design Decisions
- Inverted Index for O(1) average term lookup
- Query execution separated from ranking
- Ranking isolated for easy replacement (BM25 later)
- LRU cache to reduce repeated query latency

## Non-Goals
- Distributed execution
- Persistent on-disk index
- Unicode / multilingual tokenization
