#!/bin/bash

# Скрипт для статического анализа кода с использованием clang-tidy

set -e

echo "=== Статический анализ кода ==="

# Проверяем наличие конфигурационного файла
CONFIG_FILE=".clang-tidy"
if [[ ! -f "$CONFIG_FILE" ]]; then
    echo "❌ Конфигурационный файл $CONFIG_FILE не найден!"
    echo "   Используйте .clang-tidy или создайте симлинк на .clang-tidy.txt"
    exit 1
fi

echo "Используется конфигурация из: $CONFIG_FILE"

# Создаем каталог для отчётов если его нет
REPORTS_DIR="reports/tidy"
mkdir -p "$REPORTS_DIR"

# Файл для сводного отчёта
SUMMARY_REPORT="$REPORTS_DIR/summary.txt"

# Находим все C++ файлы в src/ (исключаем moc файлы Qt и тестовые)
FILES=$(find src -type f \( -name "*.cpp" -o -name "*.cc" -o -name "*.cxx" \) \
    ! -name "moc_*.cpp" \
    ! -name "*.moc.cpp" \
    ! -path "*/test/*" \
    ! -path "*/tests/*" \
    ! -path "*/build/*" \
    ! -path "*/.*")

if [[ -z "$FILES" ]]; then
    echo "❌ Не найдены C++ файлы для анализа в директории src/"
    exit 1
fi

ERRORS=0
WARNINGS=0
CHECKED=0

# Очищаем предыдущий сводный отчёт
> "$SUMMARY_REPORT"

# Собираем флаги для компилятора
COMPILER_FLAGS="-std=c++20 -I. -Isrc"

# Автоматически находим пути Qt если они существуют
QT_PATHS=""
if [[ -d "/usr/include/qt6" ]]; then
    QT_PATHS="$QT_PATHS -I/usr/include/qt6"
    # Добавляем основные модули Qt
    for module in QtCore QtGui QtWidgets QtNetwork QtQml QtQuick QtSql QtTest; do
        if [[ -d "/usr/include/qt6/$module" ]]; then
            QT_PATHS="$QT_PATHS -I/usr/include/qt6/$module"
        fi
    done
elif [[ -d "/usr/local/include/qt6" ]]; then
    QT_PATHS="$QT_PATHS -I/usr/local/include/qt6"
    for module in QtCore QtGui QtWidgets QtNetwork QtQml QtQuick QtSql QtTest; do
        if [[ -d "/usr/local/include/qt6/$module" ]]; then
            QT_PATHS="$QT_PATHS -I/usr/local/include/qt6/$module"
        fi
    done
fi

# Проверяем переменную окружения для Qt
if [[ -n "$QTDIR" ]]; then
    QT_PATHS="$QT_PATHS -I$QTDIR/include"
    if [[ -d "$QTDIR/include/QtCore" ]]; then
        QT_PATHS="$QT_PATHS -I$QTDIR/include/QtCore"
    fi
fi

echo "Используемые пути Qt: $QT_PATHS"

# Флаг для verbose вывода (можно установить через переменную окружения)
VERBOSE=${VERBOSE:-0}

for FILE in $FILES; do
    # Проверяем существование файла
    if [[ ! -f "$FILE" ]]; then
        echo "  ⚠️  Файл не существует: $FILE"
        continue
    fi
    
    echo "Анализ: $FILE"
    
    # Создаем имя файла для отчёта
    REPORT_NAME=$(echo "$FILE" | sed 's|^src/||; s|/|_|g')
    REPORT_FILE="$REPORTS_DIR/${REPORT_NAME}.txt"
    
    # Команда clang-tidy
    TIDY_CMD="clang-tidy \
        --config-file=$CONFIG_FILE \
        --header-filter='.*' \
        --warnings-as-errors='' \
        \"$FILE\" \
        -- \
        $COMPILER_FLAGS $QT_PATHS"
    
    if [[ $VERBOSE -eq 1 ]]; then
        echo "  Команда: $TIDY_CMD"
    fi
    
    # Выполняем анализ
    if eval $TIDY_CMD > "$REPORT_FILE" 2>&1; then
        # Проверяем содержимое отчёта
        ERR_COUNT=$(grep -c "error:" "$REPORT_FILE" || true)
        WARN_COUNT=$(grep -c "warning:" "$REPORT_FILE" || true)
        
        if [[ $ERR_COUNT -gt 0 ]] || [[ $WARN_COUNT -gt 0 ]]; then
            echo "  ⚠️  Найдено: $ERR_COUNT ошибок, $WARN_COUNT предупреждений"
            
            # Добавляем в сводный отчёт
            echo "=== $FILE ===" >> "$SUMMARY_REPORT"
            if [[ $ERR_COUNT -gt 0 ]]; then
                grep "error:" "$REPORT_FILE" | head -5 >> "$SUMMARY_REPORT"
            fi
            if [[ $WARN_COUNT -gt 0 ]]; then
                grep "warning:" "$REPORT_FILE" | head -5 >> "$SUMMARY_REPORT"
            fi
            echo "" >> "$SUMMARY_REPORT"
            
            ERRORS=$((ERRORS + ERR_COUNT))
            WARNINGS=$((WARNINGS + WARN_COUNT))
        else
            echo "  ✅ Без ошибок и предупреждений"
            # Удаляем пустой отчёт
            rm -f "$REPORT_FILE"
        fi
    else
        echo "  ❌ Ошибка выполнения clang-tidy"
        if [[ $VERBOSE -eq 1 ]] && [[ -f "$REPORT_FILE" ]]; then
            echo "  Последние строки вывода:"
            tail -10 "$REPORT_FILE"
        fi
        ERRORS=$((ERRORS + 1))
    fi
    
    CHECKED=$((CHECKED + 1))
done

echo ""
echo "=== Результаты анализа ==="
echo "Проверено файлов: $CHECKED"
echo "Найдено ошибок: $ERRORS"
echo "Найдено предупреждений: $WARNINGS"

# Выводим сводный отчёт если есть проблемы
if [[ -f "$SUMMARY_REPORT" ]] && [[ -s "$SUMMARY_REPORT" ]]; then
    echo ""
    echo "Сводный отчёт сохранён в: $SUMMARY_REPORT"
    echo ""
    echo "=== Краткий обзор проблем ==="
    head -30 "$SUMMARY_REPORT"
    
    # Сохраняем полный отчет с таймстемпом
    TIMESTAMP=$(date +"%Y%m%d_%H%M%S")
    FULL_REPORT="$REPORTS_DIR/full_report_${TIMESTAMP}.txt"
    cp "$SUMMARY_REPORT" "$FULL_REPORT"
    echo "Полный отчет сохранен как: $FULL_REPORT"
fi

# Определяем код возврата
if [[ $ERRORS -gt 0 ]]; then
    echo ""
    echo "❌ Обнаружены ошибки в коде!"
    echo "Подробные отчёты в каталоге: $REPORTS_DIR"
    exit 1
elif [[ $WARNINGS -gt 0 ]]; then
    echo ""
    echo "⚠️  Обнаружены предупреждения (но нет ошибок)"
    echo "Подробные отчёты в каталоге: $REPORTS_DIR"
    exit 0
else
    echo ""
    echo "✅ Код проходит статический анализ без ошибок и предупреждений!"
    # Очищаем каталог с отчётами если они пустые
    if [[ -d "$REPORTS_DIR" ]]; then
        find "$REPORTS_DIR" -type f -delete
        rmdir "$REPORTS_DIR" 2>/dev/null || true
    fi
    exit 0
fi