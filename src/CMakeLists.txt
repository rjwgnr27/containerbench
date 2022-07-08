find_package(benchmark REQUIRED)
include(ProcessorCount)
ProcessorCount(NPROC)

add_compile_options(-march=native -Wall -Werror -Wextra -Wpedantic)
add_executable(containerbench main.cpp
    map.cpp
    noOpVec.cpp
    sortedVec.cpp
    unorderedMap.cpp
    unsortedVec.cpp
    unsortedMutexVec.cpp
    unsortedSharedVec.cpp
)

if(NOT NPROC EQUAL 0)
    target_compile_definitions(containerbench PUBLIC -DTHREADS=${NPROC})
endif()

target_link_libraries(containerbench PRIVATE benchmark::benchmark)
