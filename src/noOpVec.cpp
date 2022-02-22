#include <cstddef>
#include <cstdint>
#include <vector>

using keyType = uint64_t;

using entryType = std::pair<keyType, void*>;

void noOpVecInitialize([[maybe_unused]] std::vector<keyType> const& fill, [[maybe_unused]] size_t count)
{
}

void *noOpVecLookup([[maybe_unused]] keyType key)
{
    return nullptr;
}
