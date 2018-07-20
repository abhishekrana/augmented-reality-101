mkdir -p build
rm -rf build/*
cd build


## Set Build Type
# Release			- Adds the -O3 -DNDEBUG flags to the compiler
# Debug				- Adds the -g flag
# MinSizeRel		- Adds -Os -DNDEBUG
# RelWithDebInfo	- Adds -O2 -g -DNDEBUG flags
# cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS="-DEX2"
cmake .. -DCMAKE_BUILD_TYPE=Debug

rm augrel101
make clean
make VERBOSE=1
./augrel101





