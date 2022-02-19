#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <shared_mutex>
#include <vector>

using entryType = std::pair<uint64_t, void*>;
static std::vector<entryType> lookupTable;
static std::shared_mutex tableMutex;

void unsortedSharedVecInitialize(std::vector<uint64_t> const& fill, size_t count)
{
    std::shared_lock lock(tableMutex);
    lookupTable.clear();
    const auto toCopy = std::min(count, fill.size());
    lookupTable.reserve(toCopy);
    for (auto begin = fill.begin(), end = begin + toCopy; begin != end; ++begin)
        lookupTable.emplace_back(*begin, reinterpret_cast<void*>(lookupTable.size()));
}

void *unsortedSharedVecLookup(uint64_t key)
{
    auto compare = [=] (entryType const& entry) {return entry.first == key;};
    std::lock_guard lock(tableMutex);
    auto const it = std::find_if(lookupTable.cbegin(), lookupTable.cend(), compare);
    return it == lookupTable.cend() ? nullptr : it->second;
}
