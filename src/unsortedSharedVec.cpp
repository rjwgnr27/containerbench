#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <shared_mutex>
#include <vector>

#if __cplusplus >= 201703L
    using smutex = std::shared_mutex;
#else
    using smutex = std::shared_timed_mutex;
#endif

using keyType = uint64_t;
using entryType = std::pair<keyType, void*>;
static std::vector<entryType> lookupTable;
static smutex tableMutex;

void unsortedSharedVecInitialize(std::vector<keyType> const& fill, size_t count)
{
    const auto toCopy = std::min(count, fill.size());
    std::lock_guard<smutex> lock(tableMutex);
    lookupTable.resize(toCopy);
    std::transform(fill.begin(), fill.begin() + toCopy, lookupTable.begin(),
                   [](keyType key){return entryType{key, nullptr};});
}

void *unsortedSharedVecLookup(keyType key)
{
    auto compare = [=] (entryType const& entry) {return entry.first == key;};
    std::shared_lock<smutex> lock(tableMutex);
    auto const it = std::find_if(lookupTable.cbegin(), lookupTable.cend(), compare);
    return it == lookupTable.cend() ? nullptr : it->second;
}
