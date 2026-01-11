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
    echo -e "${BOLD}Использование:${NC} ./scripts/$(basename $0) [ЦЕЛЬ]"
    echo ""
    echo -e "${CYAN}${BOLD}Доступные цели:${NC}"
    echo -e "  ${GREEN}build${NC}    - Сборка проекта (цель по умолчанию) ${HAMMER}"
    echo -e "  ${RED}clean${NC}    - Очистка директории сборки ${TRASH}"
    echo -e "  ${YELLOW}rebuild${NC}  - Очистка и сборка проекта ${ROCKET}"
    echo -e "  ${BLUE}help${NC}     - Вывод этой справки ${INFO}"
    echo ""
    echo -e "${CYAN}${BOLD}Примеры:${NC}"
    echo -e "  ${GREEN}./scripts/$(basename $0)${NC}           # Сборка проекта"
    echo -e "  ${GREEN}./scripts/$(basename $0) build${NC}     # Сборка проекта"
    echo -e "  ${RED}./scripts/$(basename $0) clean${NC}     # Очистка"
    echo -e "  ${YELLOW}./scripts/$(basename $0) rebuild${NC}   # Очистка и сборка"
    echo -e "  ${BLUE}./scripts/$(basename $0) help${NC}      # Справка"
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