#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <ranges>
#include <vector>

using entryType = std::pair<uint64_t, void*>;
static std::vector<entryType> lookupTable;

void sortedVecInitialize(std::vector<uint64_t> const& fill, size_t count)
{
    lookupTable.clear();
    const auto toCopy = std::min(count, fill.size());
    lookupTable.reserve(toCopy);
    for (auto begin = fill.begin(), end = begin + toCopy; begin != end; ++begin)
        lookupTable.emplace_back(*begin, reinterpret_cast<void*>(lookupTable.size()));

    std::ranges::sort(lookupTable,
            [](entryType lhs, entryType rhs){return lhs.first < rhs.first;});
}

void *sortedVecLookup(uint64_t key)
{
    auto compare = [] (entryType const& lhs, entryType const& rhs) {return lhs.first < rhs.first;};
    auto const it = std::ranges::lower_bound(lookupTable, entryType{key, nullptr}, compare);
    return it == lookupTable.cend() ? nullptr : (it->first == key ? it->second : nullptr);
}
