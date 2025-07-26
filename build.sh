#!/bin/bash
set -e

echo "Building C++ REST API..."

# Create build directories
mkdir -p build/obj
mkdir -p build/bin

# Check for g++
if command -v g++ &> /dev/null; then
    echo "Using g++ compiler..."
    g++ -std=c++17 -Wall -Wextra -O2 -I external -I src src/main.cpp -o build/bin/CppRestAPI -pthread
    echo "Build completed successfully!"
    echo "Run the application with: ./build/bin/CppRestAPI"
    exit 0
fi

# Check for clang++
if command -v clang++ &> /dev/null; then
    echo "Using clang++ compiler..."
    clang++ -std=c++17 -Wall -Wextra -O2 -I external -I src src/main.cpp -o build/bin/CppRestAPI -pthread
    echo "Build completed successfully!"
    echo "Run the application with: ./build/bin/CppRestAPI"
    exit 0
fi

echo "ERROR: No suitable C++ compiler found!"
echo "Please install g++ or clang++:"
echo "  Ubuntu/Debian: sudo apt-get install build-essential"
echo "  CentOS/RHEL:   sudo yum groupinstall 'Development Tools'"
echo "  macOS:         xcode-select --install"
exit 1