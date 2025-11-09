#!/bin/bash

set -e

echo "📚 Generating Doxygen documentation..."

# Проверка зависимостей
if ! command -v doxygen &> /dev/null; then
    echo "❌ Doxygen not installed. Please install:"
    echo "   Ubuntu: sudo apt-get install doxygen graphviz"
    echo "   RedOS: sudo dnf install doxygen graphviz"
    echo "   Windows: choco install doxygen graphviz"
    exit 1
fi

if ! command -v dot &> /dev/null; then
    echo "⚠️ Graphviz not installed. Diagrams will not be generated."
    echo "   Install: sudo apt-get install graphviz"
fi

# Сборка документации
mkdir -p build
cd build

if [ ! -f "CMakeCache.txt" ]; then
    echo "🔨 Configuring project..."
    cmake ..
fi

echo "📖 Generating documentation..."
make docs

echo ""
echo "✅ Documentation generated successfully!"
echo "📂 Location: $(pwd)/docs/html/index.html"
echo ""
echo "To view documentation:"
echo "  Linux: xdg-open docs/html/index.html"
echo "  macOS: open docs/html/index.html" 
echo "  Windows: start docs/html/index.html"