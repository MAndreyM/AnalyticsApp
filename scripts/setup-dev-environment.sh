#!/bin/bash

# ============================================================================
# СКРИПТ НАСТРОЙКИ СРЕДЫ РАЗРАБОТКИ
# Устанавливает необходимые зависимости и настраивает окружение
# ============================================================================

set -e

echo "🚀 НАСТРОЙКА СРЕДЫ РАЗРАБОТКИ ANALYTICS APP"
echo "=========================================="

# Определяем ОС
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    echo "🔍 Обнаружена Linux система"
    
    # Проверяем менеджер пакетов
    if command -v apt &> /dev/null; then
        echo "📦 Установка зависимостей через apt..."
        sudo apt update
        sudo apt install -y \
            build-essential \
            cmake \
            ninja-build \
            git \
            doxygen \
            graphviz
        
    elif command -v dnf &> /dev/null; then
        echo "📦 Установка зависимостей через dnf..."
        sudo dnf install -y \
            gcc-c++ \
            cmake \
            ninja-build \
            git \
            doxygen \
            graphviz
        
    elif command -v yum &> /dev/null; then
        echo "📦 Установка зависимостей через yum..."
        sudo yum install -y \
            gcc-c++ \
            cmake \
            ninja-build \
            git \
            doxygen \
            graphviz
    else
        echo "⚠️  Неизвестный менеджер пакетов. Установите зависимости вручную:"
        echo "   - g++ (C++20 компилятор)"
        echo "   - CMake ≥ 3.16"
        echo "   - Ninja"
        echo "   - Git"
    fi

elif [[ "$OSTYPE" == "darwin"* ]]; then
    echo "🔍 Обнаружена macOS система"
    
    if command -v brew &> /dev/null; then
        echo "📦 Установка зависимостей через Homebrew..."
        brew update
        brew install \
            cmake \
            ninja \
            git \
            doxygen \
            graphviz
    else
        echo "❌ Homebrew не установлен. Установите: https://brew.sh"
        exit 1
    fi

else
    echo "⚠️  Неподдерживаемая ОС: $OSTYPE"
    echo "   Установите зависимости вручную:"
    echo "   - C++20 компилятор"
    echo "   - CMake ≥ 3.16" 
    echo "   - Ninja"
    echo "   - Git"
fi

echo ""
echo "🔧 ПРОВЕРКА УСТАНОВЛЕННЫХ ЗАВИСИМОСТЕЙ..."
echo "------------------------------------------"

# Проверяем версии
check_dependency() {
    if command -v $1 &> /dev/null; then
        version=$($1 --version | head -n1)
        echo "✅ $1: $version"
    else
        echo "❌ $1: НЕ УСТАНОВЛЕН"
        return 1
    fi
}

check_dependency g++ || check_dependency clang++
check_dependency cmake
check_dependency ninja
check_dependency git
check_dependency doxygen

echo ""
echo "📁 НАСТРОЙКА ПРОЕКТА..."
echo "------------------------------------------"

# Создаем scripts директорию если не существует
mkdir -p scripts

# Делаем скрипты исполняемыми
chmod +x scripts/*.sh 2>/dev/null || true

echo "✅ Скрипты настроены"

echo ""
echo "🎉 НАСТРОЙКА СРЕДЫ ЗАВЕРШЕНА!"
echo "=========================================="
echo ""
echo "📝 СЛЕДУЮЩИЕ ШАГИ:"
echo "   1. Для полной сборки проекта: ./scripts/full-rebuild.sh"
echo "   2. Для быстрой пересборки:    ./scripts/quick-rebuild.sh"
echo "   3. Для запуска тестов:        cd build && ./bin/run_tests"
echo ""
echo "💡 СОВЕТ: Добавьте scripts/ в PATH для удобства:"
echo "   export PATH=\"\$PATH:$(pwd)/scripts\""