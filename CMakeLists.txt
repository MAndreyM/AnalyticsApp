cmake_minimum_required(VERSION 3.16)
project(AnalyticsApp VERSION 0.1.0 LANGUAGES CXX)

# Настройка C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Настройка генератора Ninja
if(CMAKE_GENERATOR STREQUAL "Ninja")
    message(STATUS "Using Ninja generator")
endif()

# Политики CMake
if(POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW)
endif()

# Опции проекта
option(ENABLE_TESTS "Enable tests" ON)
option(ENABLE_COVERAGE "Enable code coverage" OFF)

# Включение поддиректорий
add_subdirectory(src)

# Загрузка doctest через FetchContent если включены тесты
if(ENABLE_TESTS)
    include(FetchContent)
    FetchContent_Declare(
        doctest
        GIT_REPOSITORY https://github.com/doctest/doctest.git
        GIT_TAG v2.4.11
    )
    
    FetchContent_GetProperties(doctest)
    if(NOT doctest_POPULATED)
        FetchContent_Populate(doctest)
        # Не добавляем subdirectory, просто используем заголовочный файл
        add_library(doctest::doctest INTERFACE IMPORTED)
        target_include_directories(doctest::doctest INTERFACE ${doctest_SOURCE_DIR})
    endif()
    
    add_subdirectory(tests)
endif()