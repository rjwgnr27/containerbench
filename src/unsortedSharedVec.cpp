#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <ranges>
#include <shared_mutex>
#include <vector>

using keyType = uint64_t;
using entryType = std::pair<keyType, void*>;
static std::vector<entryType> lookupTable;
static std::shared_mutex tableMutex;

void unsortedSharedVecInitialize(std::vector<keyType> const& fill, size_t count)
{
    const auto toCopy = std::min(count, fill.size());
    std::lock_guard lock(tableMutex);
    lookupTable.resize(toCopy);
    std::transform(fill.begin(), fill.begin() + toCopy, lookupTable.begin(),
                   [](keyType key){return entryType{key, nullptr};});
}

void *unsortedSharedVecLookup(keyType key)
{
    auto compare = [=] (entryType const& entry) {return entry.first == key;};
    std::shared_lock lock(tableMutex);
    auto const it = std::ranges::find_if(lookupTable, compare);
    return it == lookupTable.cend() ? nullptr : it->second;
}
