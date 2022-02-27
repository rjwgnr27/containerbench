#include <random>
#include <ranges>
#include <vector>

#include <benchmark/benchmark.h>

namespace rng = std::ranges;

/** max number of keys in the lookup algorithm table; this is the target test */
static constexpr int MaxKeys = 4096;

/** number of test keys to look up; this many keys will be filled from a repeating
 * sub-range, each sub-range the length of the target test size
 */
static constexpr int Lookups = 8192;

using keyType = uint64_t;

static std::random_device rd;
static std::mt19937 gen{rd()};

#if defined(THREADS)
static constexpr int threads = THREADS;
#else
static constexpr int threads = 1;
#endif

static std::vector<keyType> createKeys()
{
    std::vector<keyType> keys(MaxKeys);
    rng::generate(keys, [value=gen()]() mutable {return value += gen() % 65535;});
    rng::shuffle(keys, gen);
    return keys;
}

/** table of max number of unique, randomized keys. Test lookups will be repeating
 * sub-ranges from this list */
static std::vector<keyType> allKeys = createKeys();

/** set of test keys to lookup
 *
 * Each test will use an equal number of total look-ups from varying length
 * repeated sub-sets from @c allKeys */
static std::vector<keyType> lookupKeys(Lookups);

/** call target setup function, to set up target key/value table, with the
 * test iteration specific table size */
using setupFn = void (*)(std::vector<keyType> const& fill, size_t count);
template <setupFn SETUP>
static void setup(benchmark::State const& state)
{
    auto const keyCount = state.range(0);         // number of keys in target lookup table
    SETUP(allKeys, keyCount);
    auto dest = std::copy_n(allKeys.cbegin(), keyCount, lookupKeys.begin());
    std::for_each(lookupKeys.cbegin(), lookupKeys.cend() - keyCount,
                  [&dest](auto i) mutable {*(dest++) = i;});
}


/** call target lookup function with a fixed number of lookups, on an iteration
 * specific sized sub-set of keys */
using lookupFn = void* (*)(keyType);
template <lookupFn LOOKUP>
static void lookup(benchmark::State& state)
{
    for(auto _ : state)
        rng::for_each(lookupKeys, LOOKUP);
}

void noOpVecInitialize(std::vector<keyType> const& fill, size_t count);
void *noOpVecLookup(keyType key);

void unsortedVecInitialize(std::vector<keyType> const& fill, size_t count);
void *unsortedVecLookup(keyType key);

void sortedVecInitialize(std::vector<keyType> const& fill, size_t count);
void *sortedVecLookup(keyType key);

void mapInitialize(std::vector<keyType> const& fill, size_t count);
void *mapLookup(keyType key);

void unorderedMapInitialize(std::vector<keyType> const& fill, size_t count);
void *unordedMapLookup(keyType key);

void unsortedMutexVecInitialize(std::vector<keyType> const& fill, size_t count);
void *unsortedMutexVecLookup(keyType key);

void unsortedSharedVecInitialize(std::vector<keyType> const& fill, size_t count);
void *unsortedSharedVecLookup(keyType key);

BENCHMARK(lookup<noOpVecLookup>)
    ->Name("No-op")
    ->Threads(1)
    ->Setup(setup<noOpVecInitialize>)
    ->RangeMultiplier(2)
    ->Range(1, MaxKeys);

BENCHMARK(lookup<unsortedVecLookup>)
    ->Name("Unsorted Vector")
    ->ThreadRange(1,threads)
    ->Setup(setup<unsortedVecInitialize>)
    ->RangeMultiplier(2)
    ->Range(1, MaxKeys);

BENCHMARK(lookup<unsortedMutexVecLookup>)
    ->Name("Unsorted Vector w/Mutex")
    ->ThreadRange(1,threads)
    ->Setup(setup<unsortedMutexVecInitialize>)
    ->RangeMultiplier(2)
    ->Range(1, MaxKeys);

BENCHMARK(lookup<unsortedSharedVecLookup>)
    ->Name("Vector Shared Read")
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
