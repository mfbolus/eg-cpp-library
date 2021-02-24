#!/bin/sh

# Generate sourcelist
cd scripts
./generate-lib-sourcelist.sh
cd ..

# remove cache for next cmake run
mkdir -p build
rm -f build/CMakeCache.txt

# configure the build
cd build && cmake -DEGCPP_BUILD_STATIC=1 .. && cd ..

# # generate documentation
# cd scripts
# ./generate-docs.sh
# cd ..
