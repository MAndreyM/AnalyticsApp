#!/bin/bash

# Основной скрипт для запуска всех проверок

set -e

echo "🚀 Запуск всех проверок кода"
echo "=========================="
echo ""

# Проверяем наличие утилит
command -v clang-format >/dev/null 2>&1 || { 
    echo "❌ Ошибка: clang-format не установлен"
    exit 1
}

command -v clang-tidy >/dev/null 2>&1 || { 
    echo "⚠️  Предупреждение: clang-tidy не установлен"
    echo "Пропускаем статический анализ"
    SKIP_TIDY=true
}

# Шаг 1: Проверка форматирования
echo "1️⃣  Проверка форматирования..."
if ./scripts/check-format.sh; then
    echo "✅ Форматирование проверено успешно"
else
    echo ""
    echo "❌ Проверка форматирования не пройдена"
    exit 1
fi

echo ""

# Шаг 2: Статический анализ (если clang-tidy установлен)
if [[ -z "$SKIP_TIDY" ]]; then
    echo "2️⃣  Статический анализ..."
    if ./scripts/check-tidy.sh; then
        echo "✅ Статический анализ пройден"
    else
        echo ""
        echo "❌ Статический анализ не пройден"
        exit 1
    fi
else
    echo "2️⃣  Статический анализ пропущен (clang-tidy не установлен)"
fi

echo ""
echo "================================="
echo "🎉 Все проверки пройдены успешно!"
echo "================================="