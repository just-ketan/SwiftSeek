# SwiftSeek – Benchmarks & Performance

This document describes how SwiftSeek performance is measured
and what the results mean.

---

## 🧪 Benchmark Setup

- Platform: Linux (x86_64)
- Compiler: GCC / Clang
- Flags: `-O2`
- Dataset: synthetic + real-text samples
- Query mix:
  - term queries
  - AND / OR queries
  - phrase queries

---

## 📊 Key Metrics

| Metric | Description |
|-----|-----------|
| Query latency | Time per query |
| Cache hit ratio | % queries served from cache |
| Vocabulary size | Unique indexed terms |
| Index build time | Indexing performance |

---

## ⏱️ Sample Results

| Configuration | Avg Query Time |
|--------------|----------------|
| Naive execution | ~2.4 ms |
| With caching | ~0.9 ms |

~60% latency reduction for repeated queries. 

---

## 🔍 Observations

- Inverted index dominates performance gains
- Phrase verification cost is negligible after candidate filtering
- LRU cache significantly improves tail latency

---

## ⚠️ Notes

Benchmarks are intended to compare **relative improvements**, not absolute throughput.
Results may vary by hardware and dataset.

---

## ▶️ Running Benchmarks

```bash
./scripts/run_benchmarks.sh
python scripts/generate_report.py