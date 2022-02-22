#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <ranges>
#include <vector>

using keyType = uint64_t;
using entryType = std::pair<keyType, void*>;
static std::vector<entryType> lookupTable;

void unsortedVecInitialize(std::vector<keyType> const& fill, size_t count)
{
    lookupTable.clear();
    const auto toCopy = std::min(count, fill.size());
    lookupTable.resize(toCopy);
    std::transform(fill.begin(), fill.begin() + toCopy, lookupTable.begin(),
                   [](keyType key){return entryType{key, nullptr};});
}

void *unsortedVecLookup(keyType key)
{
    auto const it = std::ranges::find_if(lookupTable,
                [=] (entryType const& entry) {return entry.first == key;});
    return it == lookupTable.end() ? nullptr : it->second;
}
