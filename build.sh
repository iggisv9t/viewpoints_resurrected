#!/bin/bash

# Create build directory
mkdir -p build
cd build

# Configure with CMake
cmake -DCMAKE_BUILD_TYPE=Release ..

# Build the project
make -j$(nproc)

echo "\nBuild complete! Run with: ./build/vp"
