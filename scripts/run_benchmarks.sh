#!/bin/bash
set -e

echo "Running SwiftSeek benchmarks..."

mkdir -p build
cd build

cmake ..
make -j$(nproc)

./swiftseek_benchmark
