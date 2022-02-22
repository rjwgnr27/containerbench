#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <mutex>
#include <vector>

using keyType = uint64_t;
using entryType = std::pair<keyType, void*>;
static std::vector<entryType> lookupTable;
static std::mutex tableMutex;

void unsortedMutexVecInitialize(std::vector<keyType> const& fill, size_t count)
{
    std::lock_guard lock(tableMutex);
    const auto toCopy = std::min(count, fill.size());
    lookupTable.resize(toCopy);
    std::transform(fill.begin(), fill.begin() + toCopy, lookupTable.begin(),
                   [](keyType key){return entryType{key, nullptr};});
}

void *unsortedMutexVecLookup(keyType key)
{
    auto compare = [] (entryType const& lhs, entryType const& rhs) {return lhs.first < rhs.first;};
    std::lock_guard lock(tableMutex);
    auto const it = std::ranges::lower_bound(lookupTable, entryType{key, nullptr}, compare);
    return it == lookupTable.end() ? nullptr : (it->first == key ? it->second : nullptr);
}
