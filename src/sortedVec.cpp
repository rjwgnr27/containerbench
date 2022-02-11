#include <algorithm>
#include <cstdint>
#include <stdexcept>
#include <vector>

using entryType = std::pair<uint64_t, void*>;
static std::vector<entryType> lookupTable;

void initializeLookup(std::vector<uint64_t> const& fill)
{
    lookupTable.clear();
    lookupTable.reserve(fill.size());
    for (auto key : fill)
        lookupTable.emplace_back(key, reinterpret_cast<void*>(lookupTable.size()));
    std::ranges::sort(lookupTable, 
            [](entryType lhs, entryType rhs){return lhs.first < rhs.first;});
}

void *lookup(uint64_t key)
{
    auto compare = [] (entryType const& lhs, entryType const& rhs) {return lhs.first < rhs.first;};
    auto const it = std::ranges::lower_bound(lookupTable, entryType{key, nullptr}, compare);
    return it == lookupTable.cend() ? nullptr : (it->first == key ? it->second : nullptr);
}