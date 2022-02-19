find_package(benchmark REQUIRED)
include(ProcessorCount)
ProcessorCount(NPROC)

add_compile_options(-O3 --std=c++20 -march=native -Wall -Werror -Wextra)
add_executable(containerbench main.cpp
    map.cpp
    noOpVec.cpp
    sortedVec.cpp
    unorderedMap.cpp
    unsortedVec.cpp
    unsortedMutexVec.cpp
    unsortedSharedVec.cpp
)
if(NOT N EQUAL 0)
    target_compile_definitions(containerbench PUBLIC -DTHREADS=${NPROC})
endif()
target_link_libraries(containerbench PRIVATE benchmark::benchmark)
