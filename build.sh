#!/usr/bin/env bash

# Create the build directory
echo "Creating build directory"
build_dir="$(dirname "$0")/build"
mkdir -p $build_dir

echo "Running cmake builds"
cmake -B $build_dir
cmake --build $build_dir

# You can run it with
# ./build/rayTracer (has debug symbols enabled)
