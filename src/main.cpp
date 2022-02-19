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


void noOpVecInitializeLookup(std::vector<uint64_t> const& fill, size_t count);
void *noOpVecLookup(uint64_t key);
static void BM_setup_noOpVec(benchmark::State const& state)
{
    noOpVecInitializeLookup(keys, state.range(0));
}

static void BM_lookup_noOpVec(benchmark::State& state)
{
    for(auto _ : state)
        for(auto key : keys)
            noOpVecLookup(key);
}

void unsortedVecInitializeLookup(std::vector<uint64_t> const& fill, size_t count);
void *unsortedVecLookup(uint64_t key);
static void BM_setup_unsortedVec(benchmark::State const& state)
{
    unsortedVecInitializeLookup(keys, state.range(0));
}

static void BM_lookup_unsortedVec(benchmark::State& state)
{
    for(auto _ : state)
        for(auto key : keys)
            unsortedVecLookup(key);
}

void sortedVecInitializeLookup(std::vector<uint64_t> const& fill, size_t count);
void *sortedVecLookup(uint64_t key);
static void BM_setup_sortedVec(benchmark::State const& state)
{
    sortedVecInitializeLookup(keys, state.range(0));
}

static void BM_lookup_sortedVec(benchmark::State& state)
{
    for(auto _ : state)
        for(auto key : keys)
            sortedVecLookup(key);
}

void mapInitializeLookup(std::vector<uint64_t> const& fill, size_t count);
void *mapLookup(uint64_t key);
static void BM_setup_map(benchmark::State const& state)
{
    mapInitializeLookup(keys, state.range(0));
}

static void BM_lookup_map(benchmark::State& state)
{
    for(auto _ : state)
        for(auto key : keys)
            mapLookup(key);
}

void unorderedMapInitializeLookup(std::vector<uint64_t> const& fill, size_t count);
void *unordedMapLookup(uint64_t key);
static void BM_setup_unordedMap(benchmark::State const& state)
{
    unorderedMapInitializeLookup(keys, state.range(0));
}

static void BM_lookup_unordedMap(benchmark::State& state)
{
    for(auto _ : state)
        for(auto key : keys)
            unordedMapLookup(key);
}

void unsortedMutexVecInitializeLookup(std::vector<uint64_t> const& fill, size_t count);
void unsortedMutexVecLookup(uint64_t key);
static void BM_setup_unsortedMutexVec(benchmark::State const& state)
{
   unsortedMutexVecInitializeLookup(keys, state.range(0));
}

static void BM_lookup_unsortedMutexVec(benchmark::State& state)
{
    for(auto _ : state)
        for(auto key : keys)
            unsortedMutexVecLookup(key);
}

void unsortedSharedVecInitializeLookup(std::vector<uint64_t> const& fill, size_t count);
void unsortedSharedVecLookup(uint64_t key);
static void BM_setup_unsortedSharedVec(benchmark::State const& state)
{
   unsortedSharedVecInitializeLookup(keys, state.range(0));
}

static void BM_lookup_unsortedSharedVec(benchmark::State& state)
{
    for(auto _ : state)
        for(auto key : keys)
            unsortedSharedVecLookup(key);
}

BENCHMARK(BM_lookup_noOpVec)->Name("No-op")->Setup(BM_setup_noOpVec)->RangeMultiplier(2)->Range(1, MaxKeys);
BENCHMARK(BM_lookup_unsortedVec)->Name("Unsorted Vector")->Setup(BM_setup_unsortedVec)->RangeMultiplier(2)->Range(1, MaxKeys);
BENCHMARK(BM_lookup_unsortedMutexVec)->Name("Vector w/Mutex")->ThreadRange(1,threads)->Setup(BM_setup_unsortedMutexVec)->RangeMultiplier(2)->Range(1, MaxKeys);
BENCHMARK(BM_lookup_unsortedSharedVec)->Name("Vector shared read")->ThreadRange(1,threads)->Setup(BM_setup_unsortedSharedVec)->RangeMultiplier(2)->Range(1, MaxKeys);
BENCHMARK(BM_lookup_sortedVec)->Name("Sorted Vector")->Setup(BM_setup_sortedVec)->RangeMultiplier(2)->Range(1, MaxKeys);
BENCHMARK(BM_lookup_map)->Name("Map")->Setup(BM_setup_map)->RangeMultiplier(2)->Range(1, MaxKeys);
BENCHMARK(BM_lookup_unordedMap)->Name("Unordered Map")->Setup(BM_setup_unordedMap)->RangeMultiplier(2)->Range(1, MaxKeys);

BENCHMARK_MAIN();
