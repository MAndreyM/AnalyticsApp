#!/bin/bash

# Скрипт для проверки форматирования кода с использованием clang-format
# Находит все файлы C++ в src/ и проверяет их соответствие стилю

set -e

echo "=== Проверка форматирования кода ==="

# Создаем временный файл для сравнения
TEMP_FILE=$(mktemp)

# Находим все C++ файлы в src/
FILES=$(find src -name "*.cpp" -o -name "*.cc" -o -name "*.cxx" -o -name "*.h" -o -name "*.hh" -o -name "*.hxx" -o -name "*.hpp")

ERRORS=0
CHECKED=0

for FILE in $FILES; do
    # Проверяем существование файла
    if [[ ! -f "$FILE" ]]; then
        continue
    fi
    
    echo "Проверка: $FILE"
    
    # Применяем форматирование к временному файлу
    clang-format -style=file "$FILE" > "$TEMP_FILE"
    
    # Сравниваем с оригиналом
    if ! diff -u "$FILE" "$TEMP_FILE" > /dev/null; then
        echo "  ❌ Требуется форматирование"
        echo "  Для исправления запустите: clang-format -style=file -i $FILE"
        ERRORS=$((ERRORS + 1))
        
        # Показываем разницу (первые 10 строк)
        echo "  Пример различий:"
        diff -u "$FILE" "$TEMP_FILE" | head -20 | sed 's/^/    /'
    else
        echo "  ✅ Форматирование корректно"
    fi
    
    CHECKED=$((CHECKED + 1))
done

# Удаляем временный файл
rm -f "$TEMP_FILE"

echo ""
echo "=== Результаты проверки ==="
echo "Проверено файлов: $CHECKED"
echo "Файлов с ошибками форматирования: $ERRORS"

if [[ $ERRORS -gt 0 ]]; then
    echo ""
    echo "❌ Обнаружены файлы с некорректным форматированием!"
    echo "Запустите scripts/fix-format.sh для автоматического исправления"
    exit 1
else
    echo ""
    echo "✅ Все файлы корректно отформатированы!"
    exit 0
fi