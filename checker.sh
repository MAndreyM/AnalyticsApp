#!/bin/bash
# checker.sh - Скрипт проверки инкрементальной TDD-версии Дня 6
# Автоматически проверяет каждый шаг и критерии достижения цели

set -e  # Выход при ошибке

# Цвета для вывода
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Переменные
PROJECT_ROOT="$(pwd)"
SRC_DIR="$PROJECT_ROOT/src"
CORE_DIR="$SRC_DIR/core"
PARSERS_DIR="$SRC_DIR/parsers"
TESTS_DIR="$PROJECT_ROOT/tests"
UNIT_TESTS_DIR="$TESTS_DIR/unit"
BUILD_DIR="$PROJECT_ROOT/build"
DOCTEST_DIR="$PROJECT_ROOT/third_party/doctest"
LOGS_DIR="$PROJECT_ROOT/logs"

# Счетчики
TOTAL_STEPS=0
PASSED_STEPS=0
FAILED_STEPS=0

# Создание каталога logs, если он не существует
if [ ! -d "$LOGS_DIR" ]; then
    echo -e "${BLUE}Создаю каталог для логов: $LOGS_DIR${NC}"
    mkdir -p "$LOGS_DIR"
fi

# Лог-файл в каталоге logs
LOG_FILE="$LOGS_DIR/checker_$(date +%Y%m%d_%H%M%S).log"

# Функции
log() {
    echo -e "$1" | tee -a "$LOG_FILE"
}

step_start() {
    ((TOTAL_STEPS++))
    log "\n${BLUE}▶ Шаг $TOTAL_STEPS: $1${NC}"
    log "   Описание: $2"
}

step_pass() {
    ((PASSED_STEPS++))
    log "   ${GREEN}✓ Успех${NC}"
}

step_fail() {
    ((FAILED_STEPS++))
    log "   ${RED}✗ Ошибка${NC}"
    if [ -n "$1" ]; then
        log "   Сообщение: $1"
    fi
}

check_file_exists() {
    if [ -f "$1" ]; then
        return 0
    else
        return 1
    fi
}

check_compile() {
    local file="$1"
    local extra_includes="$2"
    local test_name="$3"
    
    log "   Компиляция: $test_name"
    
    # Создаем временный файл для компиляции
    TEMP_CPP="/tmp/test_compile_$$.cpp"
    TEMP_EXE="/tmp/test_compile_$$.exe"
    
    cat > "$TEMP_CPP" << EOF
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
$extra_includes

TEST_CASE("Compile test: $test_name") {
    CHECK(true);
}
EOF
    
    # Компилируем
    if g++ -std=c++20 -I"$SRC_DIR" -I"$DOCTEST_DIR" "$TEMP_CPP" -o "$TEMP_EXE" 2>> "$LOG_FILE"; then
        rm -f "$TEMP_CPP" "$TEMP_EXE"
        return 0
    else
        rm -f "$TEMP_CPP" "$TEMP_EXE"
        return 1
    fi
}

check_test_runs() {
    local test_file="$1"
    local test_name="$2"
    
    log "   Запуск тестов: $test_name"
    
    # Компилируем и запускаем тесты
    if g++ -std=c++20 -I"$SRC_DIR" -I"$DOCTEST_DIR" "$test_file" -o /tmp/test_runner 2>> "$LOG_FILE"; then
        if /tmp/test_runner --success >> "$LOG_FILE" 2>&1; then
            rm -f /tmp/test_runner
            return 0
        else
            rm -f /tmp/test_runner
            return 1
        fi
    else
        return 1
    fi
}

# Начало проверки
log "${BLUE}========================================${NC}"
log "${BLUE}  ПРОВЕРКА ИНКРЕМЕНТАЛЬНОЙ TDD-ВЕРСИИ  ${NC}"
log "${BLUE}  День 6: Базовые заголовочные файлы   ${NC}"
log "${BLUE}========================================${NC}"
log "Дата: $(date)"
log "Директория проекта: $PROJECT_ROOT"
log "Директория логов: $LOGS_DIR"
log "Лог-файл: $LOG_FILE"

# ========================================
# Проверка структуры директорий
# ========================================
step_start "Структура директорий" "Проверка существования всех необходимых директорий"

DIRS_EXIST=0
for dir in "$SRC_DIR" "$CORE_DIR" "$PARSERS_DIR" "$TESTS_DIR" "$UNIT_TESTS_DIR" "$LOGS_DIR" "$DOCTEST_DIR"; do
    if [ -d "$dir" ]; then
        log "   ✓ $dir"
        ((DIRS_EXIST++))
    else
        log "   ✗ $dir - отсутствует"
    fi
done

if [ $DIRS_EXIST -eq 7 ]; then
    step_pass
else
    step_fail "Отсутствуют некоторые директории"
fi

# ========================================
# ЭТАП 0: Инфраструктура
# ========================================
log "\n${YELLOW}═ ЭТАП 0: ИНФРАСТРУКТУРА ═${NC}"

# Шаг 0.1: CMakeLists.txt для тестов
step_start "CMakeLists.txt" "Проверка файла сборки тестов"

if check_file_exists "$TESTS_DIR/CMakeLists.txt"; then
    if grep -q "add_executable.*tests" "$TESTS_DIR/CMakeLists.txt" && \
       grep -q "cxx_std_20" "$TESTS_DIR/CMakeLists.txt"; then
        step_pass
    else
        step_fail "CMakeLists.txt не содержит необходимых настроек"
    fi
else
    step_fail "Файл $TESTS_DIR/CMakeLists.txt не найден"
fi

# Шаг 0.2: Базовый тестовый файл
step_start "Базовый тестовый файл" "Проверка компиляции базового теста"

if check_file_exists "$UNIT_TESTS_DIR/test_structures.cpp"; then
    # Создаем минимальный тестовый файл для проверки
    TEMP_TEST="/tmp/base_test_$$.cpp"
    cat > "$TEMP_TEST" << 'EOF'
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

TEST_CASE("Basic test") {
    CHECK(1 + 1 == 2);
}
EOF

    if g++ -std=c++20 -I"$DOCTEST_DIR" "$TEMP_TEST" -o /tmp/base_test 2>> "$LOG_FILE"; then
        if /tmp/base_test >> "$LOG_FILE" 2>&1; then
            step_pass
        else
            step_fail "Тест не проходит"
        fi
    else
        step_fail "Ошибка компиляции"
    fi
    rm -f "$TEMP_TEST" /tmp/base_test
else
    step_fail "Базовый тестовый файл не найден"
fi

# ========================================
# ЭТАП 1: Простые структуры
# ========================================
log "\n${YELLOW}═ ЭТАП 1: ПРОСТЫЕ СТРУКТУРЫ ═${NC}"

# Шаг 1.1: StudentCategory
step_start "StudentCategory.hpp" "Проверка перечисления категорий"

if check_file_exists "$CORE_DIR/StudentCategory.hpp"; then
    # Проверяем содержимое файла
    if grep -q "enum class StudentCategory" "$CORE_DIR/StudentCategory.hpp" && \
       grep -q "ZERO_GRADE" "$CORE_DIR/StudentCategory.hpp" && \
       grep -q "EXCELLENT" "$CORE_DIR/StudentCategory.hpp"; then
        
        # Проверяем компиляцию
        if check_compile "" "#include \"$CORE_DIR/StudentCategory.hpp\"" "StudentCategory"; then
            step_pass
        else
            step_fail "Ошибка компиляции StudentCategory"
        fi
    else
        step_fail "Файл не содержит необходимые элементы перечисления"
    fi
else
    step_fail "Файл не найден"
fi

# Шаг 1.2: FileMetadata
step_start "FileMetadata.hpp" "Проверка структуры метаданных файла"

if check_file_exists "$PARSERS_DIR/FileMetadata.hpp"; then
    if grep -q "struct FileMetadata" "$PARSERS_DIR/FileMetadata.hpp" && \
       grep -q "className" "$PARSERS_DIR/FileMetadata.hpp" && \
       grep -q "isValid()" "$PARSERS_DIR/FileMetadata.hpp"; then
        
        # Создаем тестовый файл для проверки
        TEST_FILE="/tmp/test_filemetadata_$$.cpp"
        cat > "$TEST_FILE" << EOF
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "$PARSERS_DIR/FileMetadata.hpp"

TEST_CASE("FileMetadata tests") {
    FileMetadata meta{"10А", "2025/2026", "25.12.2025"};
    CHECK(meta.className == "10А");
    CHECK(meta.isValid() == true);
    
    FileMetadata empty;
    CHECK(empty.isValid() == false);
}
EOF
        
        if check_test_runs "$TEST_FILE" "FileMetadata"; then
            step_pass
        else
            step_fail "Тесты FileMetadata не проходят"
        fi
        rm -f "$TEST_FILE"
    else
        step_fail "Файл не содержит необходимые поля/методы"
    fi
else
    step_fail "Файл не найден"
fi

# Шаг 1.3: SchoolSummaryView
step_start "SchoolSummaryView.hpp" "Проверка структуры сводной статистики"

if check_file_exists "$CORE_DIR/SchoolSummaryView.hpp"; then
    if grep -q "struct SchoolSummaryView" "$CORE_DIR/SchoolSummaryView.hpp" && \
       grep -q "operator==" "$CORE_DIR/SchoolSummaryView.hpp" && \
       grep -q "totalStudents" "$CORE_DIR/SchoolSummaryView.hpp"; then
        
        TEST_FILE="/tmp/test_summary_$$.cpp"
        cat > "$TEST_FILE" << EOF
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "$CORE_DIR/SchoolSummaryView.hpp"

TEST_CASE("SchoolSummaryView tests") {
    SchoolSummaryView a{100, 5, 3, 2, 1, 20, 10};
    SchoolSummaryView b{100, 5, 3, 2, 1, 20, 10};
    SchoolSummaryView c{101, 5, 3, 2, 1, 20, 10};
    
    CHECK(a == b);
    CHECK(a != c);
}
EOF
        
        if check_test_runs "$TEST_FILE" "SchoolSummaryView"; then
            step_pass
        else
            step_fail "Тесты SchoolSummaryView не проходят"
        fi
        rm -f "$TEST_FILE"
    else
        step_fail "Файл не содержит необходимые поля/методы"
    fi
else
    step_fail "Файл не найден"
fi

# ========================================
# ЭТАП 2: Student (ядро системы)
# ========================================
log "\n${YELLOW}═ ЭТАП 2: STUDENT (ЯДРО СИСТЕМЫ) ═${NC}"

# Шаг 2.1: Student.hpp (базовый)
step_start "Student.hpp (базовый)" "Проверка структуры Student с полями"

if check_file_exists "$CORE_DIR/Student.hpp"; then
    # Проверяем наличие всех полей из ТЗ
    FIELDS_PRESENT=0
    for field in "fullName" "className" "subjectScores" "subjectGrades" "category" "hasZeroGrade" "isExcluded"; do
        if grep -q "$field" "$CORE_DIR/Student.hpp"; then
            ((FIELDS_PRESENT++))
        fi
    done
    
    if [ $FIELDS_PRESENT -eq 7 ]; then
        step_pass
    else
        step_fail "Не все поля из ТЗ присутствуют (найдено: $FIELDS_PRESENT/7)"
    fi
else
    step_fail "Файл не найден"
fi

# Шаг 2.2: Student.cpp и hasGradeTwo()
step_start "Student.cpp + hasGradeTwo()" "Проверка реализации первого метода"

if check_file_exists "$CORE_DIR/Student.cpp"; then
    if grep -q "hasGradeTwo()" "$CORE_DIR/Student.cpp" && \
       grep -q "bool Student::hasGradeTwo()" "$CORE_DIR/Student.cpp"; then
        
        # Проверяем компиляцию Student.cpp
        if g++ -std=c++20 -I"$SRC_DIR" -c "$CORE_DIR/Student.cpp" -o /tmp/Student.o 2>> "$LOG_FILE"; then
            step_pass
        else
            step_fail "Ошибка компиляции Student.cpp"
        fi
    else
        step_fail "Метод hasGradeTwo() не найден в .cpp файле"
    fi
else
    step_fail "Файл Student.cpp не найден"
fi

# Шаг 2.3: Тесты для Student
step_start "Тесты для Student" "Проверка тестов основных методов"

TEST_FILE="/tmp/test_student_full_$$.cpp"
cat > "$TEST_FILE" << EOF
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <vector>
#include <algorithm>
#include "$CORE_DIR/Student.hpp"
#include "$CORE_DIR/StudentCategory.hpp"

TEST_SUITE("Student Structure Tests") {
    TEST_CASE("Student creation and basic properties") {
        Student student;
        student.fullName = "Иванов Иван Иванович";
        student.className = "10А";
        student.subjectGrades = {{"Математика", 4}, {"Физика", 5}};
        student.category = StudentCategory::REGULAR;
        student.hasZeroGrade = false;
        student.isExcluded = false;
        
        CHECK(student.fullName == "Иванов Иван Иванович");
        CHECK(student.className == "10А");
        CHECK(student.subjectGrades.size() == 2);
    }
    
    TEST_CASE("Student::hasGradeTwo()") {
        Student student;
        
        SUBCASE("Student without grade 2") {
            student.subjectGrades = {{"Математика", 4}, {"Физика", 5}};
            CHECK(student.hasGradeTwo() == false);
        }
        
        SUBCASE("Student with grade 2") {
            student.subjectGrades = {{"Математика", 2}, {"Физика", 5}};
            CHECK(student.hasGradeTwo() == true);
        }
    }
    
    TEST_CASE("Student::countGrades()") {
        Student student;
        student.subjectGrades = {
            {"Математика", 4},
            {"Физика", 5},
            {"Химия", 4},
            {"История", 3}
        };
        
        CHECK(student.countGrades(4) == 2);
        CHECK(student.countGrades(5) == 1);
        CHECK(student.countGrades(3) == 1);
    }
}
EOF

if check_test_runs "$TEST_FILE" "Student tests"; then
    step_pass
else
    step_fail "Тесты Student не проходят"
fi
rm -f "$TEST_FILE"

# Проверка всех методов Student
step_start "Все методы Student" "Проверка наличия всех методов из ТЗ"

METHODS_PRESENT=0
for method in "hasGradeTwo" "hasSingleGrade" "hasOnlyGrades" "getSubjectsWithGrade" "countGrades" "determineCategory"; do
    if grep -q "$method" "$CORE_DIR/Student.hpp"; then
        ((METHODS_PRESENT++))
        log "   ✓ $method()"
    else
        log "   ✗ $method() - отсутствует"
    fi
done

if [ $METHODS_PRESENT -eq 6 ]; then
    step_pass
else
    step_fail "Не все методы присутствуют (найдено: $METHODS_PRESENT/6)"
fi

# ========================================
# ЭТАП 3: ClassData
# ========================================
log "\n${YELLOW}═ ЭТАП 3: CLASSDATA ═${NC}"

# Шаг 3.1: ClassData.hpp
step_start "ClassData.hpp" "Проверка структуры данных класса"

if check_file_exists "$CORE_DIR/ClassData.hpp"; then
    # Проверяем наличие полей
    CLASS_FIELDS_PRESENT=0
    for field in "className" "gradeNumber" "classLetter" "students" "subjects" "studentsWithZero" "studentsWithTwos" "studentsWithSingleThree" "studentsWithSingleFour" "studentsWithFoursAndFives" "excellentStudents"; do
        if grep -q "$field" "$CORE_DIR/ClassData.hpp"; then
            ((CLASS_FIELDS_PRESENT++))
        fi
    done
    
    # Проверяем методы
    if grep -q "getTotalStudents()" "$CORE_DIR/ClassData.hpp" && \
       grep -q "getAnalyzedStudents()" "$CORE_DIR/ClassData.hpp"; then
        
        if [ $CLASS_FIELDS_PRESENT -ge 11 ]; then
            step_pass
        else
            step_fail "Не все поля присутствуют (найдено: $CLASS_FIELDS_PRESENT/11+)"
        fi
    else
        step_fail "Методы getTotalStudents/getAnalyzedStudents отсутствуют"
    fi
else
    step_fail "Файл не найден"
fi

# ========================================
# ЭТАП 4: SchoolData
# ========================================
log "\n${YELLOW}═ ЭТАП 4: SCHOOLDATA ═${NC}"

# Шаг 4.1: SchoolData.hpp
step_start "SchoolData.hpp" "Проверка структуры данных школы"

if check_file_exists "$CORE_DIR/SchoolData.hpp"; then
    if grep -q "class SchoolData" "$CORE_DIR/SchoolData.hpp" && \
       grep -q "std::map.*classes" "$CORE_DIR/SchoolData.hpp" && \
       grep -q "getAvailableGrades()" "$CORE_DIR/SchoolData.hpp" && \
       grep -q "getSchoolSummary()" "$CORE_DIR/SchoolData.hpp"; then
        step_pass
    else
        step_fail "Файл не содержит необходимые элементы"
    fi
else
    step_fail "Файл не найден"
fi

# Шаг 4.2: SchoolData.cpp
step_start "SchoolData.cpp" "Проверка реализации методов"

if check_file_exists "$CORE_DIR/SchoolData.cpp"; then
    # Проверяем компиляцию
    if g++ -std=c++20 -I"$SRC_DIR" -c "$CORE_DIR/SchoolData.cpp" -o /tmp/SchoolData.o 2>> "$LOG_FILE"; then
        step_pass
    else
        step_fail "Ошибка компиляции SchoolData.cpp"
    fi
else
    step_fail "Файл не найден"
fi

# ========================================
# ЭТАП 5: Вспомогательные структуры
# ========================================
log "\n${YELLOW}═ ЭТАП 5: ВСПОМОГАТЕЛЬНЫЕ СТРУКТУРЫ ═${NC}"

# Шаг 5.1: ITableParser.hpp
step_start "ITableParser.hpp" "Проверка интерфейса парсера"

if check_file_exists "$PARSERS_DIR/ITableParser.hpp"; then
    if grep -q "class ITableParser" "$PARSERS_DIR/ITableParser.hpp" && \
       grep -q "virtual.*parse" "$PARSERS_DIR/ITableParser.hpp" && \
       grep -q "virtual.*extractMetadata" "$PARSERS_DIR/ITableParser.hpp"; then
        
        # Проверяем компиляцию
        if check_compile "" "#include \"$PARSERS_DIR/ITableParser.hpp\"" "ITableParser"; then
            step_pass
        else
            step_fail "Ошибка компиляции ITableParser"
        fi
    else
        step_fail "Интерфейс не содержит необходимые виртуальные методы"
    fi
else
    step_fail "Файл не найден"
fi

# ========================================
# Проверка всех тестов вместе
# ========================================
log "\n${YELLOW}═ ИНТЕГРАЦИОННАЯ ПРОВЕРКА ═${NC}"

step_start "Все тесты вместе" "Компиляция и запуск всех тестов"

FINAL_TEST="/tmp/final_test_$$.cpp"
cat > "$FINAL_TEST" << 'EOF'
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <vector>
#include <algorithm>

// Включаем все наши заголовки
#include "src/core/StudentCategory.hpp"
#include "src/parsers/FileMetadata.hpp"
#include "src/core/SchoolSummaryView.hpp"
#include "src/core/Student.hpp"
#include "src/core/ClassData.hpp"
#include "src/core/SchoolData.hpp"
#include "src/parsers/ITableParser.hpp"

TEST_SUITE("Final Integration Tests") {
    TEST_CASE("All structures can be instantiated") {
        // StudentCategory
        StudentCategory cat = StudentCategory::REGULAR;
        CHECK(static_cast<int>(cat) >= 0);
        
        // FileMetadata
        FileMetadata meta{"10А", "2025/2026", "25.12.2025"};
        CHECK(meta.isValid());
        
        // SchoolSummaryView
        SchoolSummaryView summary{100, 5, 3, 2, 1, 20, 10};
        CHECK(summary.totalStudents == 100);
        
        // Student
        Student student;
        student.fullName = "Test Student";
        CHECK(student.fullName == "Test Student");
        
        // ClassData
        ClassData classData;
        classData.className = "10А";
        CHECK(classData.className == "10А");
        
        // SchoolData
        SchoolData school;
        auto grades = school.getAvailableGrades();
        CHECK(grades.empty());
        
        SUCCESS("Все структуры могут быть созданы");
    }
    
    TEST_CASE("Student basic methods work") {
        Student student;
        student.subjectGrades = {{"Math", 4}, {"Physics", 2}, {"Chemistry", 4}};
        
        CHECK(student.hasGradeTwo() == true);
        CHECK(student.countGrades(4) == 2);
        CHECK(student.countGrades(2) == 1);
    }
}
EOF

# Компилируем с учетом всех зависимостей
if g++ -std=c++20 -I"$PROJECT_ROOT" -I"$DOCTEST_DIR" "$FINAL_TEST" -o /tmp/final_test 2>> "$LOG_FILE"; then
    if /tmp/final_test --success >> "$LOG_FILE" 2>&1; then
        step_pass
    else
        step_fail "Интеграционные тесты не проходят"
    fi
else
    step_fail "Ошибка компиляции интеграционных тестов"
fi
rm -f "$FINAL_TEST" /tmp/final_test

# ========================================
# Проверка критериев достижения цели
# ========================================
log "\n${YELLOW}═ КРИТЕРИИ ДОСТИЖЕНИЯ ЦЕЛИ ═${NC}"

step_start "Критерий 3.1: Общие критерии" "Проверка выполнения общих требований"

CRITERIA_PASSED=0
CRITERIA_TOTAL=10

# 1. Все файлы в правильных директориях
if [ -f "$CORE_DIR/Student.hpp" ] && [ -f "$CORE_DIR/ClassData.hpp" ] && \
   [ -f "$CORE_DIR/SchoolData.hpp" ] && [ -f "$PARSERS_DIR/ITableParser.hpp" ]; then
    log "   ✓ Все файлы созданы в правильных директориях"
    ((CRITERIA_PASSED++))
else
    log "   ✗ Не все файлы в правильных директориях"
fi

# 2. Полный набор полей
# Проверяем на примере Student
if grep -q "std::string fullName" "$CORE_DIR/Student.hpp" && \
   grep -q "std::unordered_map.*subjectGrades" "$CORE_DIR/Student.hpp"; then
    log "   ✓ Все структуры содержат полный набор полей"
    ((CRITERIA_PASSED++))
else
    log "   ✗ Не все поля присутствуют"
fi

# 3. Реализованы все простые методы
if grep -q "hasGradeTwo()" "$CORE_DIR/Student.hpp" && \
   grep -q "getTotalStudents()" "$CORE_DIR/ClassData.hpp" && \
   grep -q "getAvailableGrades()" "$CORE_DIR/SchoolData.hpp"; then
    log "   ✓ Реализованы все простые методы"
    ((CRITERIA_PASSED++))
else
    log "   ✗ Не все простые методы реализованы"
fi

# 4. Сложные методы имеют заглушки
if grep -q "TODO.*determineCategory" "$CORE_DIR/Student.cpp" || \
   grep -q "TODO.*getSchoolSummary" "$CORE_DIR/SchoolData.cpp"; then
    log "   ✓ Сложные методы имеют заглушки с TODO"
    ((CRITERIA_PASSED++))
else
    log "   ✗ Заглушки с TODO отсутствуют"
fi

# 5. Написаны базовые юнит-тесты
if [ -f "$UNIT_TESTS_DIR/test_structures.cpp" ]; then
    TEST_LINES=$(wc -l < "$UNIT_TESTS_DIR/test_structures.cpp" 2>/dev/null || echo 0)
    if [ "$TEST_LINES" -gt 50 ]; then
        log "   ✓ Написаны базовые юнит-тесты"
        ((CRITERIA_PASSED++))
    else
        log "   ✗ Тесты недостаточно подробные"
    fi
else
    log "   ✗ Файл тестов не найден"
fi

# 6. Используются правильные типы данных C++20
if grep -q "std::unordered_map" "$CORE_DIR/Student.hpp" && \
   grep -q "std::vector" "$CORE_DIR/ClassData.hpp"; then
    log "   ✓ Используются правильные типы данных C++20"
    ((CRITERIA_PASSED++))
else
    log "   ✗ Не все типы соответствуют C++20"
fi

# 7. Правильные include директивы
if grep -q "#include.*<string>" "$CORE_DIR/Student.hpp" && \
   grep -q "#include.*<vector>" "$CORE_DIR/ClassData.hpp"; then
    log "   ✓ Правильные include директивы"
    ((CRITERIA_PASSED++))
else
    log "   ✗ Проблемы с include директивами"
fi

# 8. Doxygen комментарии
if grep -q "/\*\*" "$CORE_DIR/Student.hpp" || grep -q "///<" "$CORE_DIR/Student.hpp"; then
    log "   ✓ Присутствуют Doxygen комментарии"
    ((CRITERIA_PASSED++))
else
    log "   ✗ Doxygen комментарии отсутствуют"
fi

# 9. Проект компилируется
if g++ -std=c++20 -I"$SRC_DIR" -c "$CORE_DIR/Student.cpp" -o /tmp/check.o 2>> "$LOG_FILE"; then
    log "   ✓ Проект компилируется без ошибок"
    ((CRITERIA_PASSED++))
    rm -f /tmp/check.o
else
    log "   ✗ Ошибки компиляции"
fi

# 10. Структура проекта соответствует архитектуре
if [ -d "$SRC_DIR/core" ] && [ -d "$SRC_DIR/parsers" ] && [ -d "$TESTS_DIR/unit" ] && [ -d "$LOGS_DIR" ]; then
    log "   ✓ Структура проекта соответствует архитектурному документу"
    ((CRITERIA_PASSED++))
else
    log "   ✗ Структура проекта не соответствует"
fi

if [ $CRITERIA_PASSED -eq $CRITERIA_TOTAL ]; then
    step_pass
    log "   Результат: $CRITERIA_PASSED/$CRITERIA_TOTAL критериев выполнено"
else
    step_fail "Выполнено только $CRITERIA_PASSED/$CRITERIA_TOTAL критериев"
fi

# ========================================
# Итоговая статистика
# ========================================
log "\n${BLUE}════════════════════════════════════════${NC}"
log "${BLUE}            ИТОГОВАЯ СТАТИСТИКА          ${NC}"
log "${BLUE}════════════════════════════════════════${NC}"

SUCCESS_RATE=$((PASSED_STEPS * 100 / TOTAL_STEPS))

log "Всего шагов проверено: $TOTAL_STEPS"
log "Успешно: ${GREEN}$PASSED_STEPS${NC}"
log "С ошибками: ${RED}$FAILED_STEPS${NC}"
log "Процент успеха: ${YELLOW}$SUCCESS_RATE%${NC}"

log "\nКритериев выполнено: ${GREEN}$CRITERIA_PASSED/$CRITERIA_TOTAL${NC}"

if [ $FAILED_STEPS -eq 0 ] && [ $CRITERIA_PASSED -eq $CRITERIA_TOTAL ]; then
    log "\n${GREEN}════════════════════════════════════════${NC}"
    log "${GREEN}  ЦЕЛЬ ДНЯ 6 ДОСТИГНУТА УСПЕШНО!       ${NC}"
    log "${GREEN}════════════════════════════════════════${NC}"
    exit 0
else
    log "\n${RED}════════════════════════════════════════${NC}"
    log "${RED}  ЕСТЬ НЕВЫПОЛНЕННЫЕ КРИТЕРИИ!           ${NC}"
    log "${RED}════════════════════════════════════════${NC}"
    
    if [ $FAILED_STEPS -gt 0 ]; then
        log "Проверьте следующие шаги:"
        grep -n "✗ Ошибка" "$LOG_FILE" | head -10
    fi
    
    exit 1
fi