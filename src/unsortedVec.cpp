#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <vector>

using entryType = std::pair<uint64_t, void*>;
static std::vector<entryType> lookupTable;

void unsortedVecInitializeLookup(std::vector<uint64_t> const& fill, size_t count)
{
    lookupTable.clear();
    const auto toCopy = std::min(count, fill.size());
    lookupTable.reserve(toCopy);
    for (auto begin = fill.begin(), end = begin + toCopy; begin != end; ++begin)
        lookupTable.emplace_back(*begin, reinterpret_cast<void*>(lookupTable.size()));
}

void *unsortedVecLookup(uint64_t key)
{
    auto compare = [=] (entryType const& entry) {return entry.first == key;};
    auto const it = std::find_if(lookupTable.cbegin(), lookupTable.cend(), compare);
    return it == lookupTable.cend() ? nullptr : it->second;
}
