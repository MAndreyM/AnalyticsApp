cmake_minimum_required(VERSION 3.16)
project(AnalyticsApp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_GENERATOR STREQUAL "Ninja")
    message(STATUS "Using Ninja generator")
endif()

if(POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW)
endif()

if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(PkgConfig REQUIRED)

add_executable(analytics_app src/main.cpp)

install(TARGETS analytics_app
    RUNTIME DESTINATION bin
    COMPONENT applications
)

enable_testing()

find_package(Doxygen)
if(DOXYGEN_FOUND)
    message(STATUS "Doxygen found - documentation available")
endif()