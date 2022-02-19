#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <vector>

using entryType = std::pair<uint64_t, void*>;
static std::vector<entryType> lookupTable;

void noOpVecInitialize(std::vector<uint64_t> const& fill, size_t count)
{
    const auto toCopy = std::min(count, fill.size());
    if (lookupTable.size() != toCopy) {
        lookupTable.clear();
        lookupTable.reserve(toCopy);
        for (auto begin = fill.begin(), end = begin + toCopy; begin != end; ++begin)
            lookupTable.emplace_back(*begin, reinterpret_cast<void*>(lookupTable.size()));
    }
}

void *noOpVecLookup([[maybe_unused]] uint64_t key)
{
    return nullptr;
}
