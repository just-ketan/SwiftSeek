#include "benchmark_runner.hpp"
#include "../core/query/query_parse.hpp"
#include "../core/query/query_executor.hpp"
#include "../core/inverted_index/inverted_index.hpp"
#include "../utils/logger.hpp"
#include <chrono>

void BenchmarkRunner::runSearchBenchmark(const std::vector<std::string>& queries){
    using clock = std::chrono::high_resolution_clock;
    InvertedIndex index;
    auto start = clock::now();
    for(const auto& q:queries){
        auto parsed = QueryParser::parse(q);
        QueryExecutor::execute(parsed, index);
    }
    auto end = clock.now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);

    log(LogLevel::INFO, "Benchmark completed in " + std::to_string(ms.count()) + "ms");
}