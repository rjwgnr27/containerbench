#include <algorithm>
#include <cstdint>
#include <stdexcept>
#include <map>

static std::map<uint64_t, void*> lookupTable;

void initializeLookup(std::vector<uint64_t> const& fill)
{
    lookupTable.clear();
    for (auto key : fill)
        lookupTable.emplace(key, reinterpret_cast<void*>(lookupTable.size()));
}

void *lookup(uint64_t key)
{
    auto const it = lookupTable.find(key);
    return it == lookupTable.end() ? nullptr : it->second;
}