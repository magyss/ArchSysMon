#!/bin/bash
set -e

mkdir -p build
cd build
cmake ..
make

echo "==> Build finished. Binary-file: ./build/ArchSysMon"
