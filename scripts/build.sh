#!/bin/bash

# Скрипт для сборки проекта C++
# Запускать из корневого каталога проекта

echo "=== Начало сборки C++ проекта ==="
echo "Текущая директория: $(pwd)"
echo ""

# Определяем путь к директории сборки
BUILD_DIR="build"
SCRIPTS_DIR="scripts"

# Проверяем, запущен ли скрипт из корневого каталога
if [[ -f "$SCRIPTS_DIR/$(basename $0)" ]] || [[ -d "$SCRIPTS_DIR" ]]; then
    echo "Скрипт запущен из корневого каталога проекта."
else
    echo "ОШИБКА: Скрипт должен запускаться из корневого каталога проекта!"
    echo "Перейдите в корневую директорию и запустите: ./scripts/$(basename $0)"
    exit 1
fi

# Создаем директорию сборки
echo "Создание директории сборки: $BUILD_DIR"
if mkdir -p "$BUILD_DIR"; then
    echo "✓ Директория создана успешно"
else
    echo "✗ Ошибка при создании директории"
    exit 1
fi

# Переходим в директорию сборки
echo ""
echo "Переход в директорию сборки: $BUILD_DIR"
cd "$BUILD_DIR" || {
    echo "✗ Ошибка при переходе в директорию $BUILD_DIR"
    exit 1
}

# Генерация файлов сборки с помощью CMake
echo ""
echo "Генерация файлов сборки с помощью CMake..."
if cmake -G Ninja ..; then
    echo "✓ CMake выполнен успешно"
else
    echo "✗ Ошибка при выполнении CMake"
    exit 1
fi

# Сборка проекта с помощью Ninja
echo ""
echo "Сборка проекта с помощью Ninja..."
START_TIME=$(date +%s)

if ninja; then
    END_TIME=$(date +%s)
    DURATION=$((END_TIME - START_TIME))
    echo ""
    echo "✓ Сборка завершена успешно!"
    echo "Время сборки: $DURATION секунд"
    
    # Выводим информацию о собранных файлах
    echo ""
    echo "=== Информация о сборке ==="
    echo "Директория сборки: $(pwd)"
    
    # Находим и выводим информацию об исполняемых файлах
    EXECUTABLES=$(find . -maxdepth 1 -type f -executable 2>/dev/null || find . -maxdepth 1 -name "*.exe" 2>/dev/null)
    if [[ -n "$EXECUTABLES" ]]; then
        echo "Собранные исполняемые файлы:"
        echo "$EXECUTABLES" | while read -r file; do
            size=$(stat -f%z "$file" 2>/dev/null || stat -c%s "$file" 2>/dev/null)
            echo "  - $(basename "$file") ($((size/1024)) KB)"
        done
    else
        echo "Исполняемые файлы не найдены (возможно, собраны библиотеки)"
    fi
    
    # Проверяем наличие файлов библиотек
    LIBRARIES=$(find . -maxdepth 1 \( -name "*.a" -o -name "*.so" -o -name "*.dylib" -o -name "*.lib" -o -name "*.dll" \) 2>/dev/null)
    if [[ -n "$LIBRARIES" ]]; then
        echo "Собранные библиотеки:"
        echo "$LIBRARIES" | while read -r file; do
            size=$(stat -f%z "$file" 2>/dev/null || stat -c%s "$file" 2>/dev/null)
            echo "  - $(basename "$file") ($((size/1024)) KB)"
        done
    fi
    
    exit 0
else
    END_TIME=$(date +%s)
    DURATION=$((END_TIME - START_TIME))
    echo ""
    echo "✗ Ошибка при сборке!"
    echo "Время выполнения: $DURATION секунд"
    exit 1
fi