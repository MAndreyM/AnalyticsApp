# ============================================
# Файл: CMakeLists.txt (корневой)
# Проект: Анализ успеваемости учащихся
# Версия: 1.0
# ============================================

# Минимальная требуемая версия CMake
cmake_minimum_required(VERSION 3.16)

# Название проекта и версия
project(AnalyticsApp
    VERSION 0.1.0
    DESCRIPTION "Система анализа успеваемости учащихся на основе данных Дневник.ру"
    LANGUAGES CXX
)

# ============================================
# 1. НАСТРОЙКА КОМПИЛЯТОРА И СТАНДАРТА C++
# ============================================

# Установка стандарта C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Политика для скрытых переменных CMake
cmake_policy(SET CMP0077 NEW)

# ============================================
# 2. НАСТРОЙКА ПЛАТФОРМО-ЗАВИСИМЫХ ПАРАМЕТРОВ
# ============================================

# Определение целевой платформы
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(TARGET_OS "linux")
    message(STATUS "Целевая ОС: Linux/RedOS")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(TARGET_OS "windows")
    message(STATUS "Целевая ОС: Windows")
else()
    message(FATAL_ERROR "Неподдерживаемая ОС: ${CMAKE_SYSTEM_NAME}")
endif()

# Настройка компилятора и флагов для разных платформ
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # Настройки для GCC/Clang (Linux/RedOS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -DDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -O2 -g")
    
    # Предупреждения как ошибки в релизных сборках
    if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
    endif()
    
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # Настройки для MSVC (Windows)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /permissive-")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi /Od /DDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /DNDEBUG")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /O2 /Zi")
    
    # Отключение предупреждений для внешних библиотек
    add_compile_options(/wd4251 /wd4275)
    
else()
    message(WARNING "Используется неподдерживаемый компилятор: ${CMAKE_CXX_COMPILER_ID}")
endif()

# ============================================
# 3. НАСТРОЙКА ПУТЕЙ И КАТАЛОГОВ
# ============================================

# Основные каталоги проекта
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Каталоги для конфигураций
foreach(config Debug Release RelWithDebInfo MinSizeRel)
    string(TOUPPER ${config} config_upper)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${config_upper} ${CMAKE_BINARY_DIR}/bin/${config})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${config_upper} ${CMAKE_BINARY_DIR}/lib/${config})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${config_upper} ${CMAKE_BINARY_DIR}/lib/${config})
endforeach()

# ============================================
# 4. ПОДКЛЮЧЕНИЕ МОДУЛЕЙ CMake
# ============================================

# Модули для поиска пакетов
include(CMakeFindDependencyMacro)
include(CheckCXXCompilerFlag)

# Проверка поддержки C++20
check_cxx_compiler_flag("-std=c++20" HAS_CXX20_FLAG)
if(NOT HAS_CXX20_FLAG)
    message(FATAL_ERROR "Компилятор не поддерживает стандарт C++20")
else()
    message(STATUS "Поддержка C++20: OK")
endif()

# ============================================
# 5. ОПРЕДЕЛЕНИЕ ЦЕЛЕЙ ПРОЕКТА
# ============================================

# Основные цели проекта (будут заполнены в последующие дни)
add_subdirectory(src)  # Исходный код приложения
add_subdirectory(tests) # Тесты

# ============================================
# 6. НАСТРОЙКА ГЕНЕРАТОРА СБОРКИ
# ============================================

# Предпочтительный генератор - Ninja
if(CMAKE_GENERATOR STREQUAL "Ninja" OR CMAKE_GENERATOR MATCHES "Ninja")
    message(STATUS "Используется генератор: Ninja")
    
    # Оптимизация для Ninja
    set(CMAKE_NINJA_FORCE_RESPONSE_FILE ON CACHE BOOL "" FORCE)
    
elseif(CMAKE_GENERATOR MATCHES "Visual Studio")
    message(STATUS "Используется генератор: ${CMAKE_GENERATOR}")
    
    # Настройки для Visual Studio
    set(CMAKE_SUPPRESS_REGENERATION TRUE)
    
else()
    message(STATUS "Используется генератор: ${CMAKE_GENERATOR}")
endif()

# ============================================
# 7. ИНФОРМАЦИОННОЕ СООБЩЕНИЕ
# ============================================

message(STATUS "========================================")
message(STATUS "Проект: ${PROJECT_NAME}")
message(STATUS "Версия: ${PROJECT_VERSION}")
message(STATUS "Система: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Компилятор: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Стандарт C++: ${CMAKE_CXX_STANDARD}")
message(STATUS "Тип сборки: ${CMAKE_BUILD_TYPE}")
message(STATUS "Выходной каталог: ${CMAKE_BINARY_DIR}")
message(STATUS "========================================")