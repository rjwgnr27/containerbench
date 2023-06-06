# containerbench
Benchmark, using Google/benchmark, performance of lookups in small data sets using different container types

## Building:
make and change to build directory:
- mkdir build
- cd build

### Configure build:
```
- cmake [CONFIGURE OPTIONS] ..
```

#### CONFIGURE_OPTIONS:
```
  -DCMAKE_BUILD_TYPE=[Debug|RelWithDebInfo|Release]
```
#### Build the image:
```
- cmake --build [BUILD_OPTIONS] .
```

The executable will be built into the "src" subdirectory. Execute the tests:
- ./src/containerbench [--help]
