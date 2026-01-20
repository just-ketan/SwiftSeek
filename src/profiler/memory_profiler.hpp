#pragma once
#include <iostream>

class MemoryProfiler{
    public:
        static void snapshot(){
            #ifdef __linux__
                std::system("grep VmRSS /proc/self/status");
            #else
                std::cout<<"Memory profiling not supported on this OD \n";
            #endif
        }
};