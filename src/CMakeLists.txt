
find_package(benchmark REQUIRED)

set(COMPILE_OPTS -O3 --std=c++20 -march=native -Wall -Werror -Wextra)

function(maketarget TARG DEP)
    add_executable(${TARG} main.cpp ${DEP})
    target_compile_options(${TARG} PRIVATE ${COMPILE_OPTS})
    target_link_libraries(${TARG} PRIVATE benchmark::benchmark)
endfunction()

maketarget(map map.cpp)
maketarget(noopvec noOpVec.cpp)
maketarget(sortedvec sortedVec.cpp)
maketarget(unorderedmap unorderedMap.cpp)
maketarget(unsortedvec unsortedVec.cpp)
