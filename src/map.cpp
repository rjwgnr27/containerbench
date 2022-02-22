#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <map>

using keyType = uint64_t;
static std::map<keyType, void*> lookupTable;

void mapInitialize(std::vector<keyType> const& fill, size_t count)
{
    lookupTable.clear();
    const auto toCopy = std::min(count, fill.size());
    std::for_each(fill.begin(), fill.begin() + toCopy,
                  [](auto key){lookupTable.insert_or_assign(key, reinterpret_cast<void*>(lookupTable.size()));});
}

void *mapLookup(keyType key)
{
    auto const it = lookupTable.find(key);
    return it == lookupTable.end() ? nullptr : it->second;
}
