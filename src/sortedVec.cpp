#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <vector>

using keyType = uint64_t;
using entryType = std::pair<keyType, void*>;
static std::vector<entryType> lookupTable;

void sortedVecInitialize(std::vector<keyType> const& fill, size_t count)
{
    lookupTable.clear();
    const auto toCopy = std::min(count, fill.size());
    lookupTable.resize(toCopy);
    std::transform(fill.begin(), fill.begin() + toCopy, lookupTable.begin(),
                   [](keyType key){return entryType{key, nullptr};});
    std::sort(lookupTable.begin(), lookupTable.end(),
            [](entryType lhs, entryType rhs){return lhs.first < rhs.first;});
}

void *sortedVecLookup(keyType key)
{
    auto compare = [] (entryType const& lhs, entryType const& rhs) {return lhs.first < rhs.first;};
    auto const it = std::lower_bound(lookupTable.cbegin(), lookupTable.cend(), entryType{key, nullptr}, compare);
    return it == lookupTable.cend() ? nullptr : (it->first == key ? it->second : nullptr);
}
