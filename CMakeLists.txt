# ============================================
# Файл: CMakeLists.txt (корневой)
# Проект: Анализ успеваемости учащихся
# Версия: 1.2 (обновлено для интеграции doctest)
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

# Выходные директории
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
# 5. ПОИСК И НАСТРОЙКА QT6
# ============================================

# Поиск Qt6 с обязательными компонентами
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Xml)

message(STATUS "Qt6 версия: ${Qt6_VERSION}")
message(STATUS "Qt6 Core: ${Qt6Core_FOUND}")
message(STATUS "Qt6 Widgets: ${Qt6Widgets_FOUND}")
message(STATUS "Qt6 Xml: ${Qt6Xml_FOUND}")

# Включение автоматического подключения MOC, UIC, RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Установка директорий для MOC файлов
set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_SOURCE_DIR}/src/views")

# ============================================
# 6. ПОИСК QtXlsxWriter
# ============================================

# Поиск QtXlsxWriter через модуль
find_package(QtXlsxWriter QUIET)
if(QtXlsxWriter_FOUND)
    message(STATUS "QtXlsxWriter найден: версия ${QtXlsxWriter_VERSION}")
    message(STATUS "Включена поддержка генерации XLSX отчетов")
else()
    message(WARNING "QtXlsxWriter не найден. Генерация XLSX отчетов будет недоступна")
endif()

# ============================================
# 7. ИНТЕГРАЦИЯ DOCTEST
# ============================================

# Добавление doctest как интерфейсной библиотеки
if(EXISTS ${CMAKE_SOURCE_DIR}/third_party/doctest/doctest.h)
    message(STATUS "Doctest найден в third_party/doctest/doctest.h")
    
    # Создание интерфейсной библиотеки для doctest
    add_library(doctest INTERFACE)
    target_include_directories(doctest INTERFACE ${CMAKE_SOURCE_DIR}/third_party/doctest)
    
    # Получение версии doctest из заголовочного файла
    file(STRINGS ${CMAKE_SOURCE_DIR}/third_party/doctest/doctest.h DOCTEST_VERSION_MAJOR 
         REGEX "^#define DOCTEST_VERSION_MAJOR [0-9]+$")
    file(STRINGS ${CMAKE_SOURCE_DIR}/third_party/doctest/doctest.h DOCTEST_VERSION_MINOR 
         REGEX "^#define DOCTEST_VERSION_MINOR [0-9]+$")
    file(STRINGS ${CMAKE_SOURCE_DIR}/third_party/doctest/doctest.h DOCTEST_VERSION_PATCH 
         REGEX "^#define DOCTEST_VERSION_PATCH [0-9]+$")
    
    string(REGEX REPLACE "^#define DOCTEST_VERSION_MAJOR ([0-9]+)$" "\\1" 
           DOCTEST_VERSION_MAJOR ${DOCTEST_VERSION_MAJOR})
    string(REGEX REPLACE "^#define DOCTEST_VERSION_MINOR ([0-9]+)$" "\\1" 
           DOCTEST_VERSION_MINOR ${DOCTEST_VERSION_MINOR})
    string(REGEX REPLACE "^#define DOCTEST_VERSION_PATCH ([0-9]+)$" "\\1" 
           DOCTEST_VERSION_PATCH ${DOCTEST_VERSION_PATCH})
    
    set(DOCTEST_VERSION "${DOCTEST_VERSION_MAJOR}.${DOCTEST_VERSION_MINOR}.${DOCTEST_VERSION_PATCH}")
    message(STATUS "Doctest версия: ${DOCTEST_VERSION}")
    
    # Опции для doctest
    target_compile_definitions(doctest INTERFACE 
        DOCTEST_CONFIG_NO_SHORT_MACRO_NAMES
        DOCTEST_CONFIG_SUPER_FAST_ASSERTS
    )
else()
    message(WARNING "Doctest не найден. Тесты будут отключены")
endif()

# ============================================
# 8. НАСТРОЙКА ПЕРЕМЕННЫХ ПРОЕКТА
# ============================================

# Определение каталога с исходным кодом
set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

# Список всех библиотек проекта
set(PROJECT_LIBRARIES
    AnalyticsCore
    AnalyticsParsers
    AnalyticsServices
    AnalyticsControllers
    AnalyticsViews
)

# Список всех целей проекта
set(PROJECT_TARGETS
    ${PROJECT_LIBRARIES}
    AnalyticsApp
)

# ============================================
# 9. ДОБАВЛЕНИЕ ПОДКАТАЛОГОВ
# ============================================

# Добавление исходного кода
add_subdirectory(src)

# Добавление тестов
add_subdirectory(tests)

# Добавление примеров (опционально)
# add_subdirectory(examples)

# ============================================
# 10. НАСТРОЙКА УСТАНОВКИ (ПРЕДВАРИТЕЛЬНО)
# ============================================

# Установка заголовочных файлов
install(DIRECTORY ${PROJECT_SOURCE_DIR}/core DESTINATION include
        FILES_MATCHING PATTERN "*.hpp" PATTERN "*.h")
install(DIRECTORY ${PROJECT_SOURCE_DIR}/parsers DESTINATION include
        FILES_MATCHING PATTERN "*.hpp" PATTERN "*.h")
install(DIRECTORY ${PROJECT_SOURCE_DIR}/services DESTINATION include
        FILES_MATCHING PATTERN "*.hpp" PATTERN "*.h")
install(DIRECTORY ${PROJECT_SOURCE_DIR}/controllers DESTINATION include
        FILES_MATCHING PATTERN "*.hpp" PATTERN "*.h")
install(DIRECTORY ${PROJECT_SOURCE_DIR}/views DESTINATION include
        FILES_MATCHING PATTERN "*.hpp" PATTERN "*.h")

# ============================================
# 11. НАСТРОЙКА ГЕНЕРАТОРА СБОРКИ
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
# 12. СОЗДАНИЕ ЦЕЛЕЙ ДЛЯ ТЕСТИРОВАНИЯ
# ============================================

# Цель для запуска всех тестов
add_custom_target(run_tests
    COMMAND $<TARGET_FILE:tests> --success
    DEPENDS tests
    COMMENT "Запуск всех тестов"
    VERBATIM
)

# ============================================
# 13. ИНФОРМАЦИОННОЕ СООБЩЕНИЕ
# ============================================

message(STATUS "========================================")
message(STATUS "Проект: ${PROJECT_NAME}")
message(STATUS "Версия: ${PROJECT_VERSION}")
message(STATUS "Система: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Компилятор: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Стандарт C++: ${CMAKE_CXX_STANDARD}")
message(STATUS "Тип сборки: ${CMAKE_BUILD_TYPE}")
message(STATUS "Qt6 версия: ${Qt6_VERSION}")
if(QtXlsxWriter_FOUND)
    message(STATUS "QtXlsxWriter: ${QtXlsxWriter_VERSION}")
else()
    message(STATUS "QtXlsxWriter: НЕ НАЙДЕН")
endif()
if(TARGET doctest)
    message(STATUS "Doctest: ${DOCTEST_VERSION}")
else()
    message(STATUS "Doctest: НЕ НАЙДЕН")
endif()
message(STATUS "Директория исходников: ${PROJECT_SOURCE_DIR}")
message(STATUS "Выходной каталог: ${CMAKE_BINARY_DIR}")
message(STATUS "========================================")