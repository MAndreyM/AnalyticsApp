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

# Doxygen documentation
find_package(Doxygen)
if(DOXYGEN_FOUND)
    message(STATUS "Doxygen found - generating documentation target")
    
    set(DOXYGEN_OUTPUT_DIR ${CMAKE_BINARY_DIR}/docs)
    set(DOXYGEN_HTML_DIR ${DOXYGEN_OUTPUT_DIR}/html)
    
    # Копируем mainpage.md в билд директорию
    configure_file(
        ${CMAKE_SOURCE_DIR}/docs/mainpage.md
        ${CMAKE_BINARY_DIR}/mainpage.md
        COPYONLY
    )
    
    # Configure Doxyfile
    configure_file(
        ${CMAKE_SOURCE_DIR}/docs/Doxyfile
        ${CMAKE_BINARY_DIR}/Doxyfile
        @ONLY
    )
    
    # Add documentation target
    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )
    
    # Install documentation
    install(
        DIRECTORY ${DOXYGEN_HTML_DIR}
        DESTINATION share/doc/analytics_app
        COMPONENT documentation
    )
    
    # Сообщение о доступности документации
    message(STATUS "Documentation target 'docs' available")
    message(STATUS "Run 'make docs' to generate documentation")
else()
    message(WARNING "Doxygen not found - documentation target will not be available")
endif()
