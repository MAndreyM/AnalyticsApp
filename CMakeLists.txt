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

# Глобальные флаги компиляции
if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

# Выходные директории
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Поиск зависимостей
find_package(PkgConfig REQUIRED)

# ============================================================================
# ПОДКЛЮЧЕНИЕ ИСХОДНЫХ КОДОВ
# ============================================================================

add_subdirectory(src)

# ============================================================================
# ТЕСТИРОВАНИЕ
# ============================================================================

enable_testing()

# Будет добавлено в следующих коммитах:
# add_subdirectory(tests)

# ============================================================================
# ДОКУМЕНТАЦИЯ
# ============================================================================

find_package(Doxygen)
if(DOXYGEN_FOUND)
    message(STATUS "Doxygen found - generating documentation target")
    
    set(DOXYGEN_OUTPUT_DIR ${CMAKE_BINARY_DIR}/docs)
    set(DOXYGEN_HTML_DIR ${DOXYGEN_OUTPUT_DIR}/html)
    
    configure_file(
        ${CMAKE_SOURCE_DIR}/docs/Doxyfile
        ${CMAKE_BINARY_DIR}/Doxyfile
        @ONLY
    )
    
    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )
    
    install(
        DIRECTORY ${DOXYGEN_HTML_DIR}
        DESTINATION share/doc/analytics_app
        COMPONENT documentation
    )
    
else()
    message(WARNING "Doxygen not found - documentation target will not be available")
endif()

# ============================================================================
# УСТАНОВКА
# ============================================================================

install(TARGETS analytics_app
    RUNTIME DESTINATION bin
    COMPONENT applications
)

# ============================================================================
# ИНФОРМАЦИЯ О ПРОЕКТЕ
# ============================================================================

message(STATUS "AnalyticsApp Configuration Complete")
message(STATUS "  Version: ${PROJECT_VERSION}")
message(STATUS "  C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  Install Prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "")
message(STATUS "Project Structure:")
message(STATUS "  src/DataProcessor/ - Модуль обработки данных")
message(STATUS "  src/FileProcessor/ - Модуль работы с файлами (будущий)")
message(STATUS "  src/Utils/ - Вспомогательные утилиты (будущий)")