#!/bin/bash

set -e

echo "🔧 CI Setup Verification"
echo "========================"

check_dependency() {
    if command -v $1 >/dev/null 2>&1; then
        echo "✅ $1: $(which $1)"
        return 0
    else
        echo "❌ $1: NOT FOUND"
        return 1
    fi
}

echo "1. Checking dependencies..."
check_dependency cmake
check_dependency ninja
check_dependency g++

echo "2. Checking project structure..."
[ -f "CMakeLists.txt" ] && echo "✅ CMakeLists.txt" || echo "❌ CMakeLists.txt"
[ -f "src/main.cpp" ] && echo "✅ src/main.cpp" || echo "❌ src/main.cpp"
[ -f "README.md" ] && echo "✅ README.md" || echo "❌ README.md"

echo "3. Testing build process..."
mkdir -p build_test
cd build_test
cmake -G Ninja ..
ninja

if [ -f "bin/analytics_app" ]; then
    ./bin/analytics_app --help
    echo "✅ Build test passed"
else
    echo "❌ Build test failed"
    exit 1
fi

cd ..
echo "🎉 All checks passed! Project is ready for CI/CD"