#!/bin/bash

# Скрипт для сборки проекта C++
# Запускать из корневого каталога проекта

set -e  # Выход при первой ошибке

# Конфигурация
BUILD_DIR="build"
SCRIPTS_DIR="scripts"

# Цвета и стили
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
CYAN='\033[0;36m'
BOLD='\033[1m'
NC='\033[0m' # No Color

# Эмодзи
CHECK="✅"
CROSS="❌"
GEAR="⚙️"
HAMMER="🔨"
TRASH="🗑️"
ROCKET="🚀"
FOLDER="📁"
FILE="📄"
TEST="🧪"
LIBRARY="📚"
CLOCK="⏱️"
INFO="ℹ️"
ARROW="➡️"
STAR="⭐"
LIST="📋"
RUN="🏃"
FILTER="🔍"
ALL="👥"
SUITE="📁"
CASE="📄"

# Логирование с цветами
log_success() {
    echo -e "${GREEN}${CHECK} $1${NC}"
}

log_error() {
    echo -e "${RED}${CROSS} $1${NC}"
}

log_info() {
    echo -e "${BLUE}${INFO} $1${NC}"
}

log_step() {
    echo -e "${CYAN}${ARROW} $1${NC}"
}

log_header() {
    echo -e "${MAGENTA}${BOLD}=== $1 ===${NC}"
}

log_warning() {
    echo -e "${YELLOW}⚠️  $1${NC}"
}

# Справка
show_help() {
    echo -e "${MAGENTA}${BOLD}${STAR} Справка по использованию скрипта сборки ${STAR}${NC}"
    echo ""
    echo -e "${BOLD}Использование:${NC} ./scripts/$(basename $0) [ЦЕЛЬ] [ПАРАМЕТРЫ]"
    echo ""
    echo -e "${CYAN}${BOLD}Доступные цели:${NC}"
    echo -e "  ${GREEN}build${NC}           - Сборка проекта (цель по умолчанию) ${HAMMER}"
    echo -e "  ${RED}clean${NC}           - Очистка директории сборки ${TRASH}"
    echo -e "  ${YELLOW}rebuild${NC}         - Очистка и сборка проекта ${ROCKET}"
    echo -e "  ${CYAN}test${NC}            - Запустить все тесты ${RUN}${ALL}"
    echo -e "  ${CYAN}test <имя>${NC}      - Запустить конкретный тест или TEST_SUITE ${RUN}${FILTER}"
    echo -e "  ${BLUE}help${NC}            - Вывод этой справки ${INFO}"
    echo ""
    echo -e "${CYAN}${BOLD}Примеры:${NC}"
    echo -e "  ${GREEN}./scripts/$(basename $0)${NC}               # Сборка проекта"
    echo -e "  ${GREEN}./scripts/$(basename $0) build${NC}         # Сборка проекта"
    echo -e "  ${RED}./scripts/$(basename $0) clean${NC}         # Очистка"
    echo -e "  ${YELLOW}./scripts/$(basename $0) rebuild${NC}     # Очистка и сборка"
    echo -e "  ${CYAN}./scripts/$(basename $0) test${NC}          # Запустить все тесты"
    echo -e "  ${CYAN}./scripts/$(basename $0) test \"FileMetadata Structure\"${NC}   # Запустить тестовый сьют"
    echo -e "  ${CYAN}./scripts/$(basename $0) test \"Enum values exist\"${NC}      # Запустить конкретный тестовый кейс"
    echo -e "  ${BLUE}./scripts/$(basename $0) help${NC}          # Справка"
    echo ""
    exit 0
}

# Проверка корневой директории
check_root_dir() {
    if [[ ! -d "$SCRIPTS_DIR" ]]; then
        log_error "Скрипт должен запускаться из корневого каталога проекта!"
        echo -e "Перейдите в корневую директорию и запустите: ${BOLD}./scripts/$(basename $0) [цель]${NC}"
        echo -e "Используйте ${BLUE}./scripts/$(basename $0) help${NC} для справки"
        exit 1
    fi
}

# Проверка существования директории сборки
check_build_dir() {
    if [[ ! -d "$BUILD_DIR" ]]; then
        log_error "Директория сборки $BUILD_DIR не существует!"
        echo -e "Сначала выполните сборку проекта: ${GREEN}./scripts/$(basename $0) build${NC}"
        exit 1
    fi
}

# Проверка существования тестов
check_tests_exist() {
    if [[ ! -d "$BUILD_DIR/tests" ]]; then
        log_error "Директория тестов $BUILD_DIR/tests не существует!"
        echo -e "Возможно, тесты не были скомпилированы."
        exit 1
    fi
    
    local test_files=$(find "$BUILD_DIR/tests" -maxdepth 1 -type f -executable 2>/dev/null)
    if [[ -z "$test_files" ]]; then
        log_error "Исполняемые файлы тестов не найдены в $BUILD_DIR/tests/"
        echo -e "Проверьте, правильно ли настроена сборка тестов в CMake."
        exit 1
    fi
}

# Показать доступные тесты
show_available_tests() {
    log_header "Доступные тесты ${LIST}"
    check_build_dir
    
    local test_file="$BUILD_DIR/tests/tests"
    
    if [[ ! -f "$test_file" ]]; then
        test_file=$(find "$BUILD_DIR/tests" -maxdepth 1 -type f -executable 2>/dev/null | head -1)
    fi
    
    if [[ -f "$test_file" ]]; then
        echo -e "${CYAN}${BOLD}Тестовый файл:${NC} $(basename "$test_file")"
        echo ""
        
        # Пробуем получить список тестов из doctest
        if "$test_file" --help 2>&1 | grep -qi "doctest"; then
            echo -e "${YELLOW}Доступные тестовые сьюты и кейсы:${NC}"
            "$test_file" --list-test-cases 2>/dev/null | while read line; do
                if [[ "$line" == *"TEST_SUITE"* ]]; then
                    echo -e "${MAGENTA}${SUITE} ${line#* }${NC}"
                elif [[ "$line" == *"TEST_CASE"* ]]; then
                    echo -e "  ${CYAN}${CASE} ${line#* }${NC}"
                fi
            done
        else
            # Для других фреймворков просто показываем имя файла
            echo -e "  ${CYAN}${TEST} $(basename "$test_file")${NC}"
        fi
    else
        echo -e "${YELLOW}Тестовые файлы не найдены${NC}"
    fi
}

# Очистка
clean() {
    log_header "Очистка проекта ${TRASH}"
    
    if [[ -d "$BUILD_DIR" ]]; then
        log_step "Удаление директории: ${FOLDER} $BUILD_DIR"
        rm -rf "$BUILD_DIR"
        log_success "Директория $BUILD_DIR удалена"
    else
        log_info "Директория $BUILD_DIR не существует, нечего очищать"
    fi
    
    log_success "Очистка завершена ${CHECK}"
}

# Сборка
build() {
    log_header "Сборка C++ проекта ${GEAR}"
    echo -e "${BLUE}Текущая директория:${NC} $(pwd)"
    
    # Создаем директорию сборки
    log_step "Создание директории: ${FOLDER} $BUILD_DIR"
    mkdir -p "$BUILD_DIR"
    log_success "Директория создана"
    
    # Переходим и собираем
    log_step "Переход в директорию сборки ${ARROW}"
    cd "$BUILD_DIR"
    
    log_step "Генерация файлов сборки с помощью CMake ${GEAR}"
    cmake -G Ninja ..
    log_success "CMake выполнен успешно"
    
    log_step "Сборка проекта с помощью Ninja ${HAMMER}"
    START_TIME=$(date +%s)
    ninja
    END_TIME=$(date +%s)
    DURATION=$((END_TIME - START_TIME))
    
    echo ""
    log_success "Сборка завершена успешно! ${ROCKET}"
    echo -e "${CYAN}${CLOCK} Время сборки:${NC} $DURATION секунд"
    
    # Возвращаемся обратно
    cd ..
    
    # Показываем результаты
    show_results
}

# Показать результаты
show_results() {
    echo ""
    log_header "Результаты сборки ${STAR}"
    
    # Основные исполняемые файлы
    if [[ -d "$BUILD_DIR/bin" ]]; then
        echo -e "${GREEN}${BOLD}${FILE} Исполняемые файлы в $BUILD_DIR/bin/:${NC}"
        local bin_files=$(find "$BUILD_DIR/bin" -maxdepth 1 -type f -executable 2>/dev/null)
        if [[ -n "$bin_files" ]]; then
            echo "$bin_files" | while read file; do
                if [[ -f "$file" ]]; then
                    size=$(stat -f%z "$file" 2>/dev/null || stat -c%s "$file" 2>/dev/null || echo "0")
                    echo -e "  ${GREEN}${CHECK} $(basename "$file")${NC} ($((size/1024)) KB)"
                fi
            done
        else
            echo -e "  ${YELLOW}⚠️  (не найдены)${NC}"
        fi
    else
        echo -e "${YELLOW}${FOLDER} Директория $BUILD_DIR/bin не существует${NC}"
    fi
    
    # Тесты
    if [[ -d "$BUILD_DIR/tests" ]]; then
        echo ""
        echo -e "${CYAN}${BOLD}${TEST} Тесты в $BUILD_DIR/tests/:${NC}"
        local test_files=$(find "$BUILD_DIR/tests" -maxdepth 1 -type f -executable 2>/dev/null)
        if [[ -n "$test_files" ]]; then
            echo "$test_files" | while read file; do
                if [[ -f "$file" ]]; then
                    size=$(stat -f%z "$file" 2>/dev/null || stat -c%s "$file" 2>/dev/null || echo "0")
                    echo -e "  ${CYAN}${TEST} $(basename "$file")${NC} ($((size/1024)) KB)"
                fi
            done
        else
            echo -e "  ${YELLOW}⚠️  (не найдены)${NC}"
        fi
    else
        echo -e "${YELLOW}${FOLDER} Директория $BUILD_DIR/tests не существует${NC}"
    fi
    
    # Библиотеки
    echo ""
    echo -e "${MAGENTA}${BOLD}${LIBRARY} Библиотеки в $BUILD_DIR/:${NC}"
    local lib_files=$(find "$BUILD_DIR" -maxdepth 1 \( -name "*.a" -o -name "*.so" -o -name "*.dylib" -o -name "*.lib" -o -name "*.dll" \) 2>/dev/null)
    if [[ -n "$lib_files" ]]; then
        echo "$lib_files" | while read file; do
            if [[ -f "$file" ]]; then
                size=$(stat -f%z "$file" 2>/dev/null || stat -c%s "$file" 2>/dev/null || echo "0")
                echo -e "  ${MAGENTA}${LIBRARY} $(basename "$file")${NC} ($((size/1024)) KB)"
            fi
        done
    else
        echo -e "  ${YELLOW}⚠️  (нет библиотек)${NC}"
    fi
    
    echo ""
    log_success "Готово! Проект успешно собран ${ROCKET}"
    echo -e "${GREEN}${BOLD}🎉 Поздравляем с успешной сборкой! 🎉${NC}"
}

# Пересборка
rebuild() {
    log_header "Пересборка проекта ${ROCKET}"
    echo -e "${YELLOW}Выполняется полная пересборка...${NC}"
    echo ""
    
    clean
    echo ""
    build
}

# Запустить все тесты
run_all_tests() {
    log_header "Запуск всех тестов ${RUN}${ALL}"
    check_build_dir
    check_tests_exist
    
    local test_files=$(find "$BUILD_DIR/tests" -maxdepth 1 -type f -executable 2>/dev/null)
    local total_tests=$(echo "$test_files" | wc -l | tr -d ' ')
    
    if [[ $total_tests -eq 0 ]]; then
        log_error "Тесты не найдены!"
        exit 1
    fi
    
    echo -e "${CYAN}${BOLD}Найдено тестовых файлов:${NC} $total_tests"
    echo ""
    
    local passed_count=0
    local failed_count=0
    local total_time=0
    
    while read test_file; do
        if [[ -f "$test_file" ]]; then
            test_name=$(basename "$test_file")
            echo -e "${CYAN}${ARROW} Запуск теста:${NC} ${BOLD}$test_name${NC}"
            
            # Определяем тестовый фреймворк для красивого вывода
            if "$test_file" --help 2>&1 | grep -qi "doctest"; then
                echo -e "${YELLOW}Фреймворк:${NC} doctest"
            elif "$test_file" --help 2>&1 | grep -qi "gtest"; then
                echo -e "${YELLOW}Фреймворк:${NC} Google Test"
            elif "$test_file" --help 2>&1 | grep -qi "catch"; then
                echo -e "${YELLOW}Фреймворк:${NC} Catch2"
            fi
            
            START_TIME=$(date +%s%N)
            
            # Запускаем тест
            if "$test_file"; then
                echo -e "${GREEN}${CHECK} Тест $test_name пройден успешно${NC}"
                ((passed_count++))
            else
                echo -e "${RED}${CROSS} Тест $test_name не пройден${NC}"
                ((failed_count++))
            fi
            
            END_TIME=$(date +%s%N)
            DURATION_MS=$(((END_TIME - START_TIME) / 1000000))
            total_time=$((total_time + DURATION_MS))
            
            echo -e "  ${CLOCK} Время выполнения: ${DURATION_MS} мс"
            echo ""
        fi
    done <<< "$test_files"
    
    # Итоги
    log_header "Результаты тестирования ${TEST}"
    echo -e "${CYAN}${BOLD}Всего тестовых файлов:${NC} $total_tests"
    echo -e "${GREEN}${BOLD}Пройдено:${NC} $passed_count"
    echo -e "${RED}${BOLD}Не пройдено:${NC} $failed_count"
    echo -e "${CYAN}${BOLD}Общее время:${NC} $total_time мс"
    echo ""
    
    if [[ $failed_count -eq 0 ]]; then
        log_success "Все тесты пройдены успешно! ${CHECK}${CHECK}${CHECK}"
        exit 0
    else
        log_error "$failed_count тестов не пройдено!"
        exit 1
    fi
}

# Запустить конкретный тест
run_specific_test() {
    local test_name="$1"
    
    if [[ -z "$test_name" ]]; then
        log_error "Не указано имя теста!"
        echo -e "Использование: ${CYAN}./scripts/$(basename $0) test <имя_теста>${NC}"
        exit 1
    fi
    
    log_header "Запуск теста: $test_name ${RUN}${FILTER}"
    check_build_dir
    check_tests_exist
    
    # Ищем тестовый файл
    local test_file="$BUILD_DIR/tests/tests"
    
    if [[ ! -f "$test_file" ]]; then
        # Попробуем найти любой исполняемый файл тестов
        test_file=$(find "$BUILD_DIR/tests" -maxdepth 1 -type f -executable 2>/dev/null | head -1)
        
        if [[ -z "$test_file" ]]; then
            log_error "Исполняемые файлы тестов не найдены!"
            exit 1
        fi
    fi
    
    echo -e "${CYAN}${ARROW} Запуск теста из:${NC} ${BOLD}$(basename "$test_file")${NC}"
    echo -e "${CYAN}${ARROW} Фильтр теста:${NC} $test_name"
    echo ""
    
    START_TIME=$(date +%s%N)
    
    # Проверяем, поддерживает ли тестовый фреймворк фильтрацию
    if "$test_file" --help 2>&1 | grep -qi "doctest"; then
        echo -e "${YELLOW}Используется doctest${NC}"
        echo -e "${YELLOW}Запуск с фильтром:${NC} --test-case=\"*$test_name*\""
        echo ""
        "$test_file" --test-case="*$test_name*"
    elif "$test_file" --help 2>&1 | grep -qi "gtest"; then
        echo -e "${YELLOW}Используется Google Test${NC}"
        echo -e "${YELLOW}Фильтр:${NC} --gtest_filter=*$test_name*"
        echo ""
        "$test_file" --gtest_color=yes --gtest_filter="*$test_name*"
    elif "$test_file" --help 2>&1 | grep -qi "catch"; then
        echo -e "${YELLOW}Используется Catch2${NC}"
        echo ""
        "$test_file" "[$test_name]" --success
    else
        echo -e "${YELLOW}Тестовый фреймворк не распознан${NC}"
        echo -e "${YELLOW}Попытка запуска со стандартными параметрами...${NC}"
        echo ""
        
        # Пробуем разные форматы фильтров
        if "$test_file" --test-case="*$test_name*" 2>/dev/null; then
            : # Успешно
        elif "$test_file" --gtest_filter="*$test_name*" 2>/dev/null; then
            : # Успешно
        elif "$test_file" "[$test_name]" 2>/dev/null; then
            : # Успешно
        else
            echo -e "${RED}Не удалось применить фильтр. Запускаем все тесты...${NC}"
            echo ""
            "$test_file"
        fi
    fi
    
    exit_code=$?
    
    END_TIME=$(date +%s%N)
    DURATION_MS=$(((END_TIME - START_TIME) / 1000000))
    
    echo ""
    log_header "Результат выполнения теста ${TEST}"
    echo -e "${CYAN}${CLOCK} Время выполнения:${NC} $DURATION_MS мс"
    echo -e "${CYAN}${ARROW} Код завершения:${NC} $exit_code"
    
    if [[ $exit_code -eq 0 ]]; then
        log_success "Тест '$test_name' пройден успешно! ${CHECK}"
        exit 0
    else
        log_error "Тест '$test_name' не пройден! ${CROSS}"
        exit $exit_code
    fi
}

# Главная функция
main() {
    check_root_dir
    
    local target="${1:-build}"
    
    case "$target" in
        build)
            build
            ;;
        clean)
            clean
            ;;
        rebuild)
            rebuild
            ;;
        test)
            if [[ -n "$2" ]]; then
                run_specific_test "$2"
            else
                run_all_tests
            fi
            ;;
        help)
            show_help
            ;;
        *)
            log_error "Неизвестная цель: $target"
            echo ""
            show_help
            exit 1
            ;;
    esac
}

# Если скрипт вызван напрямую, а не из другого скрипта
if [[ "${BASH_SOURCE[0]}" == "${0}" ]]; then
    main "$@"
fi