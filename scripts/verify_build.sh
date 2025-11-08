
#!/bin/bash

echo "Verifying build system..."

if ! command -v cmake &> /dev/null; then
    echo "ERROR: CMake is not installed"
    exit 1
fi

if ! command -v ninja &> /dev/null; then
    echo "ERROR: Ninja is not installed"
    exit 1
fi

mkdir -p build
cd build

echo "Configuring project..."
cmake -G Ninja ..

echo "Building project..."
ninja

echo "Build verification completed!"