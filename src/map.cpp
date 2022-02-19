#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <map>

static std::map<uint64_t, void*> lookupTable;

void mapInitialize(std::vector<uint64_t> const& fill, size_t count)
{
    lookupTable.clear();
    const auto toCopy = std::min(count, fill.size());
    for (auto begin = fill.begin(), end = begin + toCopy; begin != end; ++begin)
        lookupTable.emplace(*begin, reinterpret_cast<void*>(lookupTable.size()));
}

void *mapLookup(uint64_t key)
{
    auto const it = lookupTable.find(key);
    return it == lookupTable.end() ? nullptr : it->second;
}
