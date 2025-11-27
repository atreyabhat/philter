#!/bin/bash
set -e

# Directory setup
BASE_DIR=$(pwd)
RE2_DIR="$BASE_DIR/re2"
BUILD_DIR="$RE2_DIR/build_wasm"

# 1. Fetch RE2 (The "Good" Version)
if [ ! -d "$RE2_DIR" ]; then
    echo "Cloning RE2..."
    git clone https://github.com/google/re2.git "$RE2_DIR"
fi

# FORCE the specific version that works with WASM
cd "$RE2_DIR"
echo "Checking out tag 2022-12-01 (Standalone Version)..."
git checkout 2022-12-01
cd "$BASE_DIR"

# 2. Build RE2 for WASM
if [ ! -f "$BUILD_DIR/libre2.a" ]; then
    echo "Building RE2 for WebAssembly..."
    mkdir -p "$BUILD_DIR"
    cd "$BUILD_DIR"
    
    # Configure with Emscripten
    emcmake cmake "$RE2_DIR" \
        -DCMAKE_BUILD_TYPE=Release \
        -DRE2_BUILD_TESTING=OFF \
        -DCMAKE_CXX_FLAGS="-O3 -s WASM=1"

    # Build
    emmake make -j4
    cd "$BASE_DIR"
else
    echo "RE2 seems to be built already."
fi

# 3. Compile Your Code (philter.cpp)
echo "Compiling philter.cpp..."

emcc src/cpp/philter.cpp \
    -O3 \
    -s WASM=1 \
    -s MODULARIZE=1 \
    -s EXPORT_ES6=1 \
    -s ENVIRONMENT=web,worker \
    -s ALLOW_MEMORY_GROWTH=1 \
    -s DYNAMIC_EXECUTION=0 \
    --bind \
    -I "$RE2_DIR" \
    "$BUILD_DIR/libre2.a" \
    -o worker.js
    

echo "Build complete: worker.js and worker.wasm"