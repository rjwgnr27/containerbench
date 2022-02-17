find_package(benchmark REQUIRED)

add_compile_options(-O3 --std=c++20 -march=native -Wall -Werror -Wextra)
add_executable(containerbench main.cpp
    map.cpp
    noOpVec.cpp
    sortedVec.cpp
    unorderedMap.cpp
    unsortedVec.cpp
)
target_link_libraries(containerbench PRIVATE benchmark::benchmark)
