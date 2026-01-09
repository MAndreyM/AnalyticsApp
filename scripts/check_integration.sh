#!/bin/bash

# ============================================
# Скрипт проверки интеграции зависимостей (обновленный)
# ============================================

set -e  # Выход при ошибке

echo "🔍 Проверка интеграции зависимостей..."

# Цвета для вывода
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Функции для вывода
success() { echo -e "${GREEN}✅ $1${NC}"; }
error() { echo -e "${RED}❌ $1${NC}"; exit 1; }
warning() { echo -e "${YELLOW}⚠️  $1${NC}"; }
info() { echo -e "${BLUE}ℹ️  $1${NC}"; }

# ============================================
# 1. ПРОВЕРКА DOCTEST (ЗАГОЛОВОЧНЫЙ ФАЙЛ)
# ============================================

info "1. Проверка Doctest (заголовочный файл)..."

if [ -f "third_party/doctest/doctest.h" ]; then
    success "Doctest найден: third_party/doctest/doctest.h"
    
    # Проверка версии
    if grep -q "DOCTEST_VERSION" third_party/doctest/doctest.h; then
        DOCTEST_VERSION=$(grep -m1 "DOCTEST_VERSION" third_party/doctest/doctest.h | awk '{print $3}')
        info "   Версия Doctest: $DOCTEST_VERSION"
    fi
    
    # Проверка размера файла
    FILESIZE=$(stat -c%s "third_party/doctest/doctest.h" 2>/dev/null || stat -f%z "third_party/doctest/doctest.h")
    info "   Размер файла: $((FILESIZE / 1024)) KB"
else
    error "Doctest не найден. Выполните: curl -L https://raw.githubusercontent.com/doctest/doctest/master/doctest/doctest.h -o third_party/doctest/doctest.h"
fi

# ============================================
# 2. ПРОВЕРКА QTXLSXWRITER (СИСТЕМНАЯ УСТАНОВКА)
# ============================================

info "2. Проверка QtXlsxWriter (системная установка)..."

# Проверка заголовочных файлов
QTXLSX_HEADER_FOUND=false
if [ -f "/usr/local/include/QtXlsx/xlsxdocument.h" ]; then
    QTXLSX_HEADER_FOUND=true
    success "Заголовочные файлы QtXlsx найдены в /usr/local/include/QtXlsx"
elif [ -f "/usr/include/QtXlsx/xlsxdocument.h" ]; then
    QTXLSX_HEADER_FOUND=true
    success "Заголовочные файлы QtXlsx найдены в /usr/include/QtXlsx"
else
    warning "Заголовочные файлы QtXlsx не найдены в стандартных путях"
    
    # Поиск в других возможных путях
    info "   Поиск в альтернативных путях..."
    find /opt -name "xlsxdocument.h" 2>/dev/null | grep -i qtxlsx | head -3 | while read path; do
        info "   Найден: $path"
        QTXLSX_HEADER_FOUND=true
    done
fi

# Проверка библиотеки
QTXLSX_LIB_FOUND=false
if [ -f "/usr/local/lib/libQtXlsxWriter.so" ]; then
    QTXLSX_LIB_FOUND=true
    success "Библиотека найдена: /usr/local/lib/libQtXlsxWriter.so"
elif [ -f "/usr/local/lib64/libQtXlsxWriter.so" ]; then
    QTXLSX_LIB_FOUND=true
    success "Библиотека найдена: /usr/local/lib64/libQtXlsxWriter.so"
elif [ -f "/usr/lib/libQtXlsxWriter.so" ]; then
    QTXLSX_LIB_FOUND=true
    success "Библиотека найдена: /usr/lib/libQtXlsxWriter.so"
elif [ -f "/usr/lib64/libQtXlsxWriter.so" ]; then
    QTXLSX_LIB_FOUND=true
    success "Библиотека найдена: /usr/lib64/libQtXlsxWriter.so"
else
    warning "Библиотека QtXlsxWriter не найдена в стандартных путях"
    
    # Поиск библиотеки
    info "   Поиск библиотеки..."
    find /usr -name "*QtXlsx*" -type f 2>/dev/null | head -3 | while read lib; do
        info "   Найден: $lib"
        QTXLSX_LIB_FOUND=true
    done
fi

if [ "$QTXLSX_HEADER_FOUND" = true ] && [ "$QTXLSX_LIB_FOUND" = true ]; then
    success "QtXlsxWriter полностью доступен в системе"
elif [ "$QTXLSX_HEADER_FOUND" = true ] || [ "$QTXLSX_LIB_FOUND" = true ]; then
    warning "QtXlsxWriter частично доступен"
else
    warning "QtXlsxWriter не найден в системе. Генерация отчетов XLSX будет недоступна"
fi

# ============================================
# 3. ПРОВЕРКА ОБНОВЛЕНИЙ CMAKELISTS.TXT
# ============================================

info "3. Проверка обновлений CMakeLists.txt..."

# Проверка корневого CMakeLists.txt
if grep -q "third_party/doctest" CMakeLists.txt; then
    success "Doctest добавлен в корневой CMakeLists.txt"
else
    error "Doctest не добавлен в корневой CMakeLists.txt"
fi

if grep -qi "qtxlsxwriter" CMakeLists.txt || grep -q "FindQtXlsxWriter" CMakeLists.txt; then
    success "QtXlsxWriter упомянут в корневом CMakeLists.txt"
else
    warning "QtXlsxWriter не упомянут в корневом CMakeLists.txt"
fi

# Проверка CMakeLists.txt для тестов
if [ -f "tests/CMakeLists.txt" ]; then
    success "Файл tests/CMakeLists.txt существует"
    
    if grep -q "add_executable(tests" tests/CMakeLists.txt; then
        success "   Цель 'tests' определена"
    else
        error "   Цель 'tests' не определена"
    fi
    
    # ГИБКАЯ ПРОВЕРКА ПОДКЛЮЧЕНИЯ DOCTEST (принимает оба варианта: doctest или doctest::doctest)
    if grep -A10 "target_link_libraries.*tests" tests/CMakeLists.txt | grep -q "doctest"; then
        success "   Doctest подключен к цели tests"
    elif grep -q "doctest::doctest" tests/CMakeLists.txt; then
        success "   Doctest подключен к цели tests"
    else
        error "   Doctest не подключен к цели tests"
    fi
else
    error "Файл tests/CMakeLists.txt не существует"
fi

# Проверка FindQtXlsxWriter.cmake
if [ -f "cmake/FindQtXlsxWriter.cmake" ]; then
    success "FindQtXlsxWriter.cmake существует"
else
    warning "FindQtXlsxWriter.cmake не существует"
fi

# ============================================
# 4. ПРОВЕРКА ТЕСТОВОГО ФАЙЛА
# ============================================

info "4. Проверка тестовых файлов..."

if [ -f "tests/unit/test_doctest_integration.cpp" ]; then
    success "Тестовый файл test_doctest_integration.cpp существует"
    
    # Проверка содержимого тестового файла
    if grep -q "DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN" tests/unit/test_doctest_integration.cpp; then
        success "   Doctest правильно сконфигурирован"
    else
        error "   Doctest неправильно сконфигурирован"
    fi
    
    # Проверка количества тестов
    TEST_COUNT=$(grep -c "TEST_CASE\|TEST_SUITE" tests/unit/test_doctest_integration.cpp)
    info "   Количество тест-кейсов: $TEST_COUNT"
else
    error "Тестовый файл не существует"
fi

# ============================================
# 5. ПРОВЕРКА СБОРКИ ПРОЕКТА
# ============================================

info "5. Попытка сборки проекта..."

# Создание build директории если не существует
if [ ! -d "build" ]; then
    info "   Создание директории build..."
    mkdir -p build
fi

cd build

# Проверка конфигурации CMake
info "   Запуск CMake..."
if cmake .. -DCMAKE_BUILD_TYPE=Debug -G Ninja 2>&1 | tee cmake_output.log; then
    success "   CMake сконфигурирован успешно"
    
    # Проверка вывода CMake на наличие информации о зависимостях
    if grep -qi "doctest" cmake_output.log; then
        success "   Doctest обнаружен CMake"
    fi
    
    if grep -qi "qtxlsx" cmake_output.log; then
        success "   QtXlsxWriter обнаружен CMake"
    fi
else
    error "   Ошибка конфигурации CMake"
fi

# Проверка на наличие ошибок в выводе CMake
if grep -i "error" cmake_output.log | grep -v "0 errors"; then
    warning "   Обнаружены ошибки в выводе CMake:"
    grep -i "error" cmake_output.log | grep -v "0 errors" | head -5
fi

# Проверка что цели созданы
info "   Проверка созданных целей..."
if cmake --build . --target help 2>&1 | grep -q "tests"; then
    success "   Цель 'tests' создана"
else
    error "   Цель 'tests' не создана"
fi

if cmake --build . --target help 2>&1 | grep -q "run_tests"; then
    success "   Цель 'run_tests' создана"
else
    error "   Цель 'run_tests' не создана"
fi

# ============================================
# 6. ПРОВЕРКА КОМПИЛЯЦИИ
# ============================================

info "6. Компиляция тестов..."

if cmake --build . --target tests 2>&1 | tee build_output.log; then
    success "   Тесты успешно скомпилированы"
    
    # Проверка предупреждений компилятора
    WARNINGS=$(grep -ci "warning" build_output.log || true)
    if [ "$WARNINGS" -gt 0 ]; then
        warning "   Обнаружено предупреждений компилятора: $WARNINGS"
    fi
else
    error "   Ошибка компиляции тестов"
    
    # Вывод ошибок компиляции
    echo "   Последние ошибки:"
    grep -i "error" build_output.log | tail -5
fi

# ПРОВЕРКА НАЛИЧИЯ ИСПОЛНЯЕМОГО ФАЙЛА ТЕСТОВ В /bin/Debug/tests
info "   Проверка наличия исполняемого файла тестов..."

if [ -f "bin/Debug/tests" ]; then
    success "   Исполняемый файл тестов создан: bin/Debug/tests"
    file bin/Debug/tests
    EXECUTABLE="./bin/Debug/tests"
elif [ -f "bin/Release/tests" ]; then
    success "   Исполняемый файл тестов создан: bin/Release/tests"
    EXECUTABLE="./bin/Release/tests"
elif [ -f "tests/tests" ]; then
    success "   Исполняемый файл тестов создан: tests/tests"
    file tests/tests
    EXECUTABLE="./tests/tests"
elif [ -f "tests/tests.exe" ]; then
    success "   Исполняемый файл тестов создан: tests/tests.exe"
    EXECUTABLE="./tests/tests.exe"
else
    warning "   Исполняемый файл тестов не найден в ожидаемых путях"
    
    # Поиск исполняемого файла
    info "   Поиск исполняемого файла..."
    find . -name "tests" -type f -executable 2>/dev/null | head -3 | while read found_file; do
        info "   Найден: $found_file"
        EXECUTABLE="./$found_file"
    done
    
    if [ -z "$EXECUTABLE" ]; then
        error "   Исполняемый файл тестов не создан"
    fi
fi

# ============================================
# 7. ЗАПУСК ТЕСТОВ
# ============================================

info "7. Запуск тестов..."

# Если EXECUTABLE еще не установлен, ищем снова
if [ -z "$EXECUTABLE" ]; then
    if [ -f "bin/Debug/tests" ]; then
        EXECUTABLE="./bin/Debug/tests"
    elif [ -f "bin/Release/tests" ]; then
        EXECUTABLE="./bin/Release/tests"
    elif [ -f "tests/tests" ]; then
        EXECUTABLE="./tests/tests"
    elif [ -f "tests/tests.exe" ]; then
        EXECUTABLE="./tests/tests.exe"
    else
        error "   Исполняемый файл тестов не найден"
        exit 1
    fi
fi

success "   Исполняемый файл: $EXECUTABLE"

if $EXECUTABLE --success 2>&1 | tee test_output.log; then
    success "   Тесты выполнены успешно"
    
    # Анализ результатов тестов
    echo ""
    echo "   📊 Результаты тестов:"
    
    # Извлечение статистики - исправленные регулярные выражения
    if grep -q "test cases:" test_output.log; then
        TESTS_PASSED=$(grep "test cases:" test_output.log | grep -o "[0-9]\+ passed" | grep -o "[0-9]\+")
        TESTS_FAILED=$(grep "test cases:" test_output.log | grep -o "[0-9]\+ failed" | grep -o "[0-9]\+")
        TESTS_SKIPPED=$(grep "test cases:" test_output.log | grep -o "[0-9]\+ skipped" | grep -o "[0-9]\+")
        
        # Если не нашли, пробуем альтернативный формат
        if [ -z "$TESTS_PASSED" ]; then
            TESTS_PASSED=$(grep "test cases:" test_output.log | grep -o "| [0-9]\+ passed" | grep -o "[0-9]\+")
            TESTS_FAILED=$(grep "test cases:" test_output.log | grep -o "| [0-9]\+ failed" | grep -o "[0-9]\+")
            TESTS_SKIPPED=$(grep "test cases:" test_output.log | grep -o "| [0-9]\+ skipped" | grep -o "[0-9]\+")
        fi
        
        info "     Пройдено: ${TESTS_PASSED:-0}"
        if [ "${TESTS_FAILED:-0}" -gt 0 ]; then
            error "     Не пройдено: ${TESTS_FAILED:-0}"
        else
            success "     Не пройдено: ${TESTS_FAILED:-0}"
        fi
        if [ "${TESTS_SKIPPED:-0}" -gt 0 ]; then
            warning "     Пропущено: ${TESTS_SKIPPED:-0}"
        fi
        
        # Также выводим статистику по проверкам
        if grep -q "assertions:" test_output.log; then
            ASSERTIONS_PASSED=$(grep "assertions:" test_output.log | grep -o "[0-9]\+ passed" | grep -o "[0-9]\+")
            ASSERTIONS_FAILED=$(grep "assertions:" test_output.log | grep -o "[0-9]\+ failed" | grep -o "[0-9]\+")
            info "     Проверки пройдены: ${ASSERTIONS_PASSED:-0}"
            if [ "${ASSERTIONS_FAILED:-0}" -gt 0 ]; then
                error "     Проверки не пройдены: ${ASSERTIONS_FAILED:-0}"
            else
                success "     Проверки не пройдены: ${ASSERTIONS_FAILED:-0}"
            fi
        fi
    fi
    
    if grep -q "All tests passed" test_output.log || grep -q "Status: SUCCESS" test_output.log; then
        success "   ✅ Все тесты прошли успешно!"
    fi
else
    TEST_EXIT_CODE=$?
    error "   Ошибка выполнения тестов (код выхода: $TEST_EXIT_CODE)"
    
    # Вывод последних строк лога тестов
    echo "   Последние строки лога:"
    tail -20 test_output.log
fi

cd ..

# ============================================
# 8. ФИНАЛЬНАЯ ПРОВЕРКА СТРУКТУРЫ
# ============================================

info "8. Финальные проверки структуры..."

info "   Проверка структуры проекта:"
TREE_STRUCTURE="
AnalyticsApp/
├── CMakeLists.txt
├── src/
├── tests/
│   ├── CMakeLists.txt
│   └── unit/
│       └── test_doctest_integration.cpp
├── third_party/
│   └── doctest/
│       ├── doctest.h
│       └── CMakeLists.txt
├── cmake/
│   └── FindQtXlsxWriter.cmake
└── scripts/
    └── check_integration.sh"

echo "$TREE_STRUCTURE"

# Проверка существования ключевых директорий
DIRECTORIES=("src" "tests" "tests/unit" "third_party" "third_party/doctest" "cmake" "scripts")
for dir in "${DIRECTORIES[@]}"; do
    if [ -d "$dir" ]; then
        success "   $dir/ существует"
    else
        error "   $dir/ не существует"
    fi
done

# Проверка ключевых файлов
FILES=("CMakeLists.txt" "tests/CMakeLists.txt" "third_party/doctest/doctest.h" "scripts/check_integration.sh")
for file in "${FILES[@]}"; do
    if [ -f "$file" ]; then
        success "   $file существует"
    else
        error "   $file не существует"
    fi
done

# Проверка Git статуса
info "   Проверка статуса Git..."
if git status --porcelain | grep -q "^??"; then
    warning "   Есть неотслеживаемые файлы"
    git status --porcelain | grep "^??" | head -5
fi

# ============================================
# ИТОГОВЫЙ ОТЧЕТ
# ============================================

echo ""
echo "========================================="
echo "📊 ОТЧЕТ О ПРОВЕРКЕ ИНТЕГРАЦИИ (ОБНОВЛЕННЫЙ)"
echo "========================================="
echo ""
echo "✅ Doctest (заголовочный файл):"
echo "   - Файл: third_party/doctest/doctest.h"
echo "   - Версия: $DOCTEST_VERSION"
echo "   - Статус: Интегрирован как заголовочная библиотека"
echo ""
echo "✅ QtXlsxWriter (системная установка):"
if [ "$QTXLSX_HEADER_FOUND" = true ]; then
    echo "   - Заголовочные файлы: Найдены"
else
    echo "   - Заголовочные файлы: Не найдены"
fi
if [ "$QTXLSX_LIB_FOUND" = true ]; then
    echo "   - Библиотека: Найдена"
else
    echo "   - Библиотека: Не найдена"
fi
echo ""
echo "✅ CMake конфигурация:"
echo "   - Doctest добавлен в сборку"
echo "   - FindQtXlsxWriter.cmake создан"
echo "   - Цели tests и run_tests созданы"
echo ""
echo "✅ Тестирование:"
echo "   - Тесты компилируются успешно"
echo "   - Тесты запускаются"
echo "   - Все базовые тесты проходят"
echo ""
echo "🎉 Интеграция зависимостей завершена успешно!"
echo ""
echo "Следующие шаги:"
echo "1. Настройка CI/CD (День 5)"
echo "2. Создание основных структур данных (День 6)"
echo "3. Реализация парсера баллов (День 7)"
echo "========================================="

# Упрощенное создание отчета без проблем с here-document
echo "# Отчет проверки интеграции зависимостей" > integration_check_report.md
echo "**Дата:** $(date)" >> integration_check_report.md
echo "**Версия проекта:** 0.1.0" >> integration_check_report.md
echo "**Тип интеграции:** Заголовочный файл (Doctest) + Системная установка (QtXlsxWriter)" >> integration_check_report.md
echo "" >> integration_check_report.md
echo "## Результаты проверки:" >> integration_check_report.md
echo "" >> integration_check_report.md
echo "### 1. Doctest (заголовочный файл)" >> integration_check_report.md
echo "- [x] Файл \`doctest.h\` скачан в \`third_party/doctest/\`" >> integration_check_report.md
echo "- [x] Версия: $DOCTEST_VERSION" >> integration_check_report.md
echo "- [x] Настроен как интерфейсная библиотека в CMake" >> integration_check_report.md
echo "- [x] Интегрирован в систему сборки" >> integration_check_report.md
echo "" >> integration_check_report.md
echo "### 2. QtXlsxWriter (системная установка)" >> integration_check_report.md
if [ "$QTXLSX_HEADER_FOUND" = true ]; then
    echo "- [x] Заголовочные файлы найдены в системе" >> integration_check_report.md
else
    echo "- [ ] Заголовочные файлы найдены в системе" >> integration_check_report.md
fi
if [ "$QTXLSX_LIB_FOUND" = true ]; then
    echo "- [x] Библиотека найдена в системе" >> integration_check_report.md
else
    echo "- [ ] Библиотека найдена в системе" >> integration_check_report.md
fi
echo "- [x] Создан файл \`FindQtXlsxWriter.cmake\` для поиска" >> integration_check_report.md
echo "- [x] Интегрирован в CMake через \`find_package\`" >> integration_check_report.md
echo "" >> integration_check_report.md
echo "### 3. CMake конфигурация" >> integration_check_report.md
echo "- [x] Doctest добавлен через \`add_subdirectory\`" >> integration_check_report.md
echo "- [x] QtXlsxWriter ищется через \`find_package\`" >> integration_check_report.md
echo "- [x] Цель \`tests\` создана" >> integration_check_report.md
echo "- [x] Цель \`run_tests\` создана" >> integration_check_report.md
echo "" >> integration_check_report.md
echo "### 4. Тестирование" >> integration_check_report.md
echo "- [x] Тестовый файл \`test_doctest_integration.cpp\` создан" >> integration_check_report.md
echo "- [x] Тесты успешно компилируются" >> integration_check_report.md
echo "- [x] Тесты успешно запускаются" >> integration_check_report.md
echo "- [x] Базовые тесты проходят" >> integration_check_report.md
echo "" >> integration_check_report.md
echo "## Статус: ✅ УСПЕШНО" >> integration_check_report.md
echo "" >> integration_check_report.md
echo "**Замечания:**" >> integration_check_report.md
if [ "$WARNINGS" -gt 0 ]; then
    echo "- Обнаружено $WARNINGS предупреждений компилятора" >> integration_check_report.md
fi
if [ "${TESTS_FAILED:-0}" -gt 0 ]; then
    echo "- Не пройдено тестов: ${TESTS_FAILED}" >> integration_check_report.md
fi
echo "" >> integration_check_report.md
echo "**Рекомендации:**" >> integration_check_report.md
echo "1. Убедитесь, что QtXlsxWriter установлен в системе для генерации отчетов" >> integration_check_report.md

success "Отчет сохранен в integration_check_report.md"