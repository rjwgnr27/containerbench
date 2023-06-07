#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <unordered_map>
#include <vector>

using keyType = uint64_t;
static std::unordered_map<keyType, void*> lookupTable;

void unorderedMapInitialize(std::vector<keyType> const& fill, size_t count)
{
    lookupTable.clear();
    const auto toCopy = std::min(count, fill.size());
    lookupTable.reserve(toCopy);
    std::for_each(fill.begin(), fill.begin() + toCopy,
                  [](auto key){lookupTable[key] = reinterpret_cast<void*>(lookupTable.size());});
}

void *unordedMapLookup(keyType key)
{
    auto const it = lookupTable.find(key);
    return it == lookupTable.end() ? nullptr : it->second;
}
