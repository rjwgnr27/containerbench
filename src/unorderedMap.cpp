#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <unordered_map>

static std::unordered_map<uint64_t, void*> lookupTable;

void unorderedMapInitialize(std::vector<uint64_t> const& fill, size_t count)
{
    lookupTable.clear();
    const auto toCopy = std::min(count, fill.size());
    lookupTable.reserve(toCopy);
    for (auto begin = fill.begin(), end = begin + toCopy; begin != end; ++begin)
        lookupTable.emplace(*begin, reinterpret_cast<void*>(lookupTable.size()));
}

void *unordedMapLookup(uint64_t key)
{
    auto const it = lookupTable.find(key);
    return it == lookupTable.end() ? nullptr : it->second;
}
