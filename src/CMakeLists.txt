
find_package(benchmark REQUIRED)

function(maketarget TARG DEP)
    add_executable(${TARG} main.cpp ${DEP})
    target_link_libraries(${TARG} PRIVATE benchmark::benchmark)
endfunction()

add_compile_options(-O3 --std=c++20 -march=native -Wall -Werror -Wextra)

maketarget(map map.cpp)
maketarget(noopvec noOpVec.cpp)
maketarget(sortedvec sortedVec.cpp)
maketarget(unorderedmap unorderedMap.cpp)
maketarget(unsortedvec unsortedVec.cpp)
