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

if(ENABLE_TESTS)
    add_subdirectory(tests)
endif()