#pragma once
#include <chrono>
#include <function>

class TimeProfiler{
    static long long measure(const std::function<void()>& fn){
        auto start = std::chrono::high_resolution_clock::now();
        fn();
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
    }
}