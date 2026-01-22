# SwiftSeek – Design Decisions

This document explains **why** SwiftSeek is designed the way it is.

---

## ❓ Why an Inverted Index?

- Industry-standard approach
- Efficient for large document collections
- Natural fit for TF-IDF and BM25
- Simple, cache-friendly data structure

Alternatives like suffix trees were rejected due to:
- memory overhead
- poor ranking support

---

## ❓ Why Aho–Corasick?

Aho–Corasick is used **only for phrase queries**, not general retrieval.

Benefits:
- Linear-time multi-pattern matching
- No positional index required
- Clean separation from ranking logic

This avoids bloating the index while still supporting phrase search.

---

## ❓ Why TF-IDF (Initially)?

- Simple and interpretable
- Fast to compute
- Strong baseline for relevance
- Easy to replace with BM25

---

## ❓ Why LRU Cache?

- Query workloads are skewed
- Repeated queries are common
- LRU provides strong locality benefits
- O(1) operations with predictable behavior

---

## 🚫 Explicit Non-Goals (v1)

- Distributed execution
- Persistent storage
- Unicode-aware tokenization
- Near-real-time indexing

These are intentionally excluded to keep the system focused and correct.

---

## 🎯 Design Philosophy

SwiftSeek favors:
- correctness over premature optimization
- clarity over cleverness
- measurable performance gains