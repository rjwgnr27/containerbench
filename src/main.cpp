#include <cstdint>
#include <getopt.h>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <benchmark/benchmark.h>

void initializeLookup(std::vector<uint64_t> const& fill);
void *lookup(uint64_t key);

static std::vector<uint64_t> keys;

static void BM_setup(benchmark::State const& state)
{
    int nKeys = state.range(0);
    keys.clear();
    keys.reserve(nKeys);
    for (uint64_t value = rand(); nKeys--; value += static_cast<uint64_t>(rand()) % 65535l) 
        keys.push_back(value);
    
    initializeLookup(keys);
}

static void BM_lookup(benchmark::State& state)
{
    for(auto _ : state)
        for(auto key : keys)
            lookup(key);
}

BENCHMARK(BM_lookup)->RangeMultiplier(2)->Range(1, 4096)->Setup(BM_setup);
BENCHMARK_MAIN();
