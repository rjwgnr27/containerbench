# containerbench
Benchmark, using Google/benchmark, performance of lookups in small data sets using different container types

## Building:
make and change to build directory:
- mkdir build
- cd build

Configure build:
- cmake [CMAKE OPTIONS] ..

Build the image:
- cmake --build .

The executable will be built into the "src" subdirectory. Execute the tests:
- ./src/containerbench [--help]
