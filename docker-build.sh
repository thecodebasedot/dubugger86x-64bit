#!/bin/bash
set -e

# Set environment variables for MSVC and Qt
export MSVC_BIN_DIR=/root/opt/msvc/bin/x64
export QT_BIN_DIR=/x64dbg/build64/_deps/qt5-src/bin

echo "Building x64 version..."
mkdir -p build64
cmake -B build64 -DCMAKE_TOOLCHAIN_FILE=cmake/msvc-wine.cmake -G Ninja
cmake --build build64 -j$(nproc)

echo "Build complete."
