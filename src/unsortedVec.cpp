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
}

void *lookup(uint64_t key)
{
    auto compare = [=] (entryType const& entry) {return entry.first == key;};
    auto const it = std::find_if(lookupTable.cbegin(), lookupTable.cend(), compare);
    return it == lookupTable.cend() ? nullptr : it->second;
}