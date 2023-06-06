# containerbench
Benchmark, using Google/benchmark, performance of lookups in small data sets using different container types

## Building:
make and change to build directory:
```
mkdir build
cd build
```

### Configure build:
```
cmake [CONFIGURE OPTIONS] ..
```

### CONFIGURE_OPTIONS:
The following options are available for the configuration step:
```
  -DCMAKE_BUILD_TYPE=[Debug|RelWithDebInfo|Release]
```
### Build the image:
```
- cmake --build . [BUILD_OPTIONS]
```

#### BUILD_OPTIONS
```
  --clean-first       : Clean previous build
  --parallel N        : Use N concurrent threads
  --verbose           : Show the make commands
```

The executable will be built into the "src" subdirectory. Execute the tests:
```
./src/containerbench [--help]
```
