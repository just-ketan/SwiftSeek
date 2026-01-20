#  SwiftSeek  
### A High-Performance Search Engine in Modern C++

SwiftSeek is a **production-grade, single-node search engine** implemented end-to-end in **modern C++**.  
It is designed to showcase **data structures, algorithms, systems design, and performance optimization** in a clean, extensible architecture.

> ⚡ Fast indexing  
> 🔍 Efficient query execution  
> 📊 TF-IDF ranking  
> 🧠 LRU caching  
> 🧪 Benchmark-driven development  

---

## ✨ Key Features

- **Inverted Index** for O(1) average term lookup  
- **AND / OR query execution** with clean separation of concerns  
- **TF-IDF ranking** for relevance-based results  
- **LRU cache** to accelerate repeated queries  
- **Benchmark & profiler support** to measure real performance gains  
- **Modular architecture** designed for extensibility (BM25, concurrency, persistence)

---

## 🧠 Architecture Overview

```graphql
        ┌────────────┐
        │   Query    │
        └─────┬──────┘
              │
        ┌─────▼──────┐
        │  Parser    │
        └─────┬──────┘
              │
        ┌─────▼──────────┐
        │ Query Executor │◄──────┐
        └─────┬──────────┘       │
              │                  │
    ┌─────────▼────────┐   ┌─────▼─────┐
    │ Candidate Docs   │   │ LRU Cache │
    └─────────┬────────┘   └───────────┘
              │
        ┌─────▼──────┐
        │ TF-IDF     │
        │ Ranker     │
        └─────┬──────┘
              │
        ┌─────▼──────┐
        │  Results   │
        └────────────┘
```

---

## 📁 Project Structure

swiftseek/
├── src/
│ ├── core/
│ │ ├── document/ # Document storage
│ │ ├── inverted_index/ # Index + tokenizer
│ │ ├── query/ # Parser + executor
│ │ └── ranking/ # TF-IDF
│ ├── cache/ # LRU cache
│ ├── benchmark/ # Benchmarks
│ ├── profiler/ # Time & memory profiling
│ └── utils/ # Helpers
│
├── tests/ # Unit & performance tests
├── examples/ # Demo programs
├── docs/ # Design & architecture docs
├── config/ # YAML configs
└── scripts/ # Benchmark & report scripts

```

## 🔍 Example Usage

```cpp
DocumentStore store;
InvertedIndex index;

store.addDocument(1, "high performance search engine");
store.addDocument(2, "search engines use inverted index");

index.indexDocument(1, store.getDocument(1));
index.indexDocument(2, store.getDocument(2));

auto query = QueryParser::parse("search engine");
auto results = QueryExecutor::execute(query, index);

for (auto docId : results) {
    std::cout << "Found document: " << docId << std::endl;
}
```

## 📊 Ranking: TF-IDF

SwiftSeek uses classic **TF-IDF (Term Frequency–Inverse Document Frequency)** scoring to rank documents by relevance.

### Scoring Intuition
- **TF (Term Frequency)**  
  Measures how often a query term appears in a document.
- **IDF (Inverse Document Frequency)**  
  Penalizes terms that appear in many documents and boosts rare terms.

### Formula Used

```yaml
score(d) = Σ TF(t, d) × log(N / (1 + df(t)))
Where:
- `t` → query term  
- `d` → document  
- `N` → total number of documents  
- `df(t)` → number of documents containing term `t`

### Why TF-IDF?
- Simple and interpretable
- Industry-standard baseline
- Fast to compute
- Easy to extend (BM25, cosine normalization)

```

## ⚡ Performance Highlights

| Version | Avg Query Time |
|------|----------------|
| Naive execution | ~2.4 ms |
| Cached + optimized | ~0.9 ms |

📈 **~60% latency reduction** on repeated queries  
📊 Cache hit ratio stabilizes around **80–85%**

Detailed measurements and methodology are available in  
`docs/BENCHMARKS.md`.


## 🧪 Benchmarking & Profiling

SwiftSeek is built with a **benchmark-first mindset**.

### Run Benchmarks
```bash
./scripts/run_benchmarks.sh
```
```python
python scripts/generate_report.py
```

### Included Tools

High-resolution time profiling
Memory usage snapshots
Naive vs optimized comparisons
Cache hit/miss evaluation

## 🛠️ Build Instructions
        mkdir build
        cd build
        cmake ..
        make -j


### The project is tested with:
    Modern GCC / Clang
    -O2 optimization flags
    Linux-based environments

## 👨‍💻 Author Notes

SwiftSeek was built as a systems-level project to demonstrate:
##### Data structures (inverted index, LRU cache)
##### Algorithmic optimization
##### Clean C++ architecture
##### Real-world performance tradeoffs

If you are reviewing this project for interviews or hiring:
The focus is on design decisions, performance reasoning, and extensibility, not just correctness.


##### ⭐ If You Like This Project
    Star the repository ⭐
    Fork and experiment 🔧
    Use it as a foundation for your own search engine 🚀