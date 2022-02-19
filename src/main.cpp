#include <cstdint>
#include <getopt.h>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include <benchmark/benchmark.h>

static constexpr int MaxKeys = 4096;

#if defined(THREADS)
static constexpr int threads = THREADS;
#else
static constexpr int threads = 1;
#endif

static std::vector<uint64_t> createKeys()
{
    std::vector<uint64_t> keys(MaxKeys);
    std::generate(begin(keys), end(keys), [](){return static_cast<uint64_t>(rand());});
    return keys;
}

static std::vector<uint64_t> keys = createKeys();

using setupFn = void (*)(std::vector<uint64_t> const& fill, size_t count);
template <setupFn SETUP>
static void setup(benchmark::State const& state)
{
    SETUP(keys, state.range(0));
}


using lookupFn = void* (*)(uint64_t);
template <lookupFn LOOKUP>
static void lookup(benchmark::State& state)
{
    for(auto _ : state)
        for(auto key : keys)
            LOOKUP(key);
}

void noOpVecInitialize(std::vector<uint64_t> const& fill, size_t count);
void *noOpVecLookup(uint64_t key);

void unsortedVecInitialize(std::vector<uint64_t> const& fill, size_t count);
void *unsortedVecLookup(uint64_t key);

void sortedVecInitialize(std::vector<uint64_t> const& fill, size_t count);
void *sortedVecLookup(uint64_t key);

void mapInitialize(std::vector<uint64_t> const& fill, size_t count);
void *mapLookup(uint64_t key);

void unorderedMapInitialize(std::vector<uint64_t> const& fill, size_t count);
void *unordedMapLookup(uint64_t key);

void unsortedMutexVecInitialize(std::vector<uint64_t> const& fill, size_t count);
void *unsortedMutexVecLookup(uint64_t key);

void unsortedSharedVecInitialize(std::vector<uint64_t> const& fill, size_t count);
void *unsortedSharedVecLookup(uint64_t key);

BENCHMARK(lookup<noOpVecLookup>)
    ->Name("No-op")
    ->Threads(1)
    ->Setup(setup<noOpVecInitialize>)
    ->RangeMultiplier(2)
    ->Range(1, MaxKeys);

BENCHMARK(lookup<unsortedVecLookup>)
    ->Name("Unsorted Vector")
    ->Threads(1)
    ->Setup(setup<unsortedVecInitialize>)
    ->RangeMultiplier(2)
    ->Range(1, MaxKeys);

BENCHMARK(lookup<unsortedMutexVecLookup>)
    ->Name("Vector w/Mutex")
    ->ThreadRange(1,threads)
    ->Setup(setup<unsortedMutexVecInitialize>)
    ->RangeMultiplier(2)
    ->Range(1, MaxKeys);

BENCHMARK(lookup<unsortedSharedVecLookup>)
    ->Name("Vector shared read")
    ->ThreadRange(1,threads)
    ->Setup(setup<unsortedSharedVecInitialize>)
    ->RangeMultiplier(2)
    ->Range(1, MaxKeys);

BENCHMARK(lookup<sortedVecLookup>)
    ->Name("Sorted Vector")
    ->Threads(1)
    ->Setup(setup<sortedVecInitialize>)
    ->RangeMultiplier(2)
    ->Range(1, MaxKeys);

BENCHMARK(lookup<mapLookup>)
    ->Name("Map")
    ->Threads(1)
    ->Setup(setup<mapInitialize>)
    ->RangeMultiplier(2)
    ->Range(1, MaxKeys);

BENCHMARK(lookup<unordedMapLookup>)
    ->Name("Unordered Map")
    ->Threads(1)
    ->Setup(setup<unorderedMapInitialize>)
    ->RangeMultiplier(2)
    ->Range(1, MaxKeys);

BENCHMARK_MAIN();
