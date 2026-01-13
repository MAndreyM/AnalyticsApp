#!/bin/bash

# Скрипт для автоматического исправления форматирования кода

set -e

echo "=== Исправление форматирования кода ==="

# Находим все C++ файлы в src/
FILES=$(find src -name "*.cpp" -o -name "*.cc" -o -name "*.cxx" -o -name "*.h" -o -name "*.hh" -o -name "*.hxx" -o -name "*.hpp")

FIXED=0
TOTAL=0

for FILE in $FILES; do
    # Проверяем существование файла
    if [[ ! -f "$FILE" ]]; then
        continue
    fi
    
    echo "Обработка: $FILE"
    
    # Создаем резервную копию
    BACKUP="${FILE}.backup"
    cp "$FILE" "$BACKUP"
    
    # Применяем форматирование
    if clang-format -style=file -i "$FILE"; then
        # Проверяем, изменился ли файл
        if ! diff -q "$FILE" "$BACKUP" > /dev/null; then
            echo "  ✅ Исправлено"
            FIXED=$((FIXED + 1))
        else
            echo "  ⏭️  Без изменений"
        fi
    else
        echo "  ❌ Ошибка форматирования"
        # Восстанавливаем из резервной копии при ошибке
        mv "$BACKUP" "$FILE"
    fi
    
    # Удаляем резервную копию если она не нужна
    if [[ -f "$BACKUP" ]]; then
        rm -f "$BACKUP"
    fi
    
    TOTAL=$((TOTAL + 1))
done

echo ""
echo "=== Результаты ==="
echo "Обработано файлов: $TOTAL"
echo "Исправлено файлов: $FIXED"

if [[ $FIXED -gt 0 ]]; then
    echo ""
    echo "✅ Форматирование исправлено для $FIXED файлов"
else
    echo ""
    echo "ℹ️  Все файлы уже корректно отформатированы"
fi