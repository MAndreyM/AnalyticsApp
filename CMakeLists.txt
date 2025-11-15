cmake_minimum_required(VERSION 3.16)
project(AnalyticsApp VERSION 0.1.0 LANGUAGES CXX)

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

# Линковка с std::filesystem
if(MSVC)
    # MSVC автоматически линкует std::filesystem
else()
    # Для GCC и Clang нужно явно указать линковку
    find_library(STD_FILESYSTEM_LIB stdc++fs)
    if(STD_FILESYSTEM_LIB)
        message(STATUS "Found std::filesystem library: ${STD_FILESYSTEM_LIB}")
    else()
        message(STATUS "std::filesystem will be linked automatically")
    endif()
endif()

# Выходные директории
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ============================================================================
# ПОИСК ЗАВИСИМОСТЕЙ ДЛЯ EXCEL ПАРСИНГА
# ============================================================================

# Поиск библиотеки libxls для чтения XLS файлов
option(SKIP_LIBXLS_CHECK "Skip libxls dependency check" OFF)

if(NOT SKIP_LIBXLS_CHECK)
    # Сначала попробуем найти через pkg-config (Linux)
    find_package(PkgConfig)
    if(PkgConfig_FOUND)
        pkg_check_modules(LIBXLS libxls)
    endif()

    if(LIBXLS_FOUND)
        message(STATUS "✅ Found libxls via pkg-config: ${LIBXLS_VERSION}")
        message(STATUS "   Include directories: ${LIBXLS_INCLUDE_DIRS}")
        message(STATUS "   Library directories: ${LIBXLS_LIBRARY_DIRS}")
        message(STATUS "   Libraries: ${LIBXLS_LIBRARIES}")
        
        include_directories(${LIBXLS_INCLUDE_DIRS})
        link_directories(${LIBXLS_LIBRARY_DIRS})
    else()
        # Альтернативный поиск через find_library (Windows/MSYS2 и другие системы)
        find_library(LIBXLS_LIB 
            NAMES xlsreader libxlsreader
            PATHS 
                /mingw64/lib
                /usr/lib
                /usr/local/lib
                "C:/libxls/lib"
        )
        
        find_path(LIBXLS_INCLUDE_DIR 
            NAMES xls.h
            PATHS 
                /mingw64/include
                /usr/include
                /usr/local/include
                "C:/libxls/include"
        )
        
        if(LIBXLS_LIB AND LIBXLS_INCLUDE_DIR)
            message(STATUS "✅ Found libxls via find_library")
            message(STATUS "   Library: ${LIBXLS_LIB}")
            message(STATUS "   Include dir: ${LIBXLS_INCLUDE_DIR}")
            
            set(LIBXLS_FOUND TRUE)
            set(LIBXLS_LIBRARIES ${LIBXLS_LIB})
            set(LIBXLS_INCLUDE_DIRS ${LIBXLS_INCLUDE_DIR})
            include_directories(${LIBXLS_INCLUDE_DIRS})
        else()
            message(WARNING "❌ libxls not found - Excel features will be disabled")
            set(LIBXLS_FOUND FALSE)
            # Добавляем определение для условной компиляции
            add_compile_definitions(LIBXLS_DISABLED=1)
        endif()
    endif()
    
    # Добавляем определение для условной компиляции
    if(LIBXLS_FOUND)
        add_compile_definitions(HAVE_LIBXLS=1)
        message(STATUS "   Excel parsing: ENABLED")
    else()
        add_compile_definitions(HAVE_LIBXLS=0)
        message(STATUS "   Excel parsing: DISABLED")
    endif()
else()
    message(STATUS "⚠️  Skipping libxls check (manual override)")
    set(LIBXLS_FOUND FALSE)
    add_compile_definitions(HAVE_LIBXLS=0 LIBXLS_DISABLED=1)
endif()

# ============================================================================
# ПОДКЛЮЧЕНИЕ ИСХОДНЫХ КОДОВ
# ============================================================================

add_subdirectory(src)

# ============================================================================
# ТЕСТИРОВАНИЕ
# ============================================================================

enable_testing()
add_subdirectory(tests)

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

# Устанавливаем только существующие цели
if(TARGET analytics_app)
    install(TARGETS analytics_app
        RUNTIME DESTINATION bin
        COMPONENT applications
    )
endif()

if(TARGET demo_directory_scanner)
    install(TARGETS demo_directory_scanner
        RUNTIME DESTINATION bin  
        COMPONENT applications
    )
endif()

# ============================================================================
# ИНФОРМАЦИЯ О ПРОЕКТЕ
# ============================================================================

message(STATUS "")
message(STATUS "🎯 AnalyticsApp Configuration Complete")
message(STATUS "   Version: ${PROJECT_VERSION}")
message(STATUS "   C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "   Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "   System: ${CMAKE_SYSTEM_NAME}")
message(STATUS "   LibXLS Found: ${LIBXLS_FOUND}")
if(LIBXLS_FOUND)
    message(STATUS "   Excel Parsing: ENABLED")
else()
    message(STATUS "   Excel Parsing: DISABLED")
endif()
message(STATUS "")
message(STATUS "📦 Available Targets:")
message(STATUS "   analytics_app         - Main application")
message(STATUS "   demo_datamodels       - Data models demonstration") 
message(STATUS "   demo_directory_scanner - Directory scanner demonstration")
message(STATUS "   test_gradecalculator  - Grade calculator tests (4 scenarios)")
message(STATUS "   docs                  - Generate documentation")
message(STATUS "")
message(STATUS "🏗️  Project Structure:")
message(STATUS "   src/DataProcessor/    - Data models and analysis logic")
message(STATUS "   src/Utils/            - File system utilities")
message(STATUS "   src/FileProcessor/    - Directory scanning and Excel file processing")
message(STATUS "")
message(STATUS "🚀 Current Features:")
message(STATUS "   ✅ Data models with validation")
message(STATUS "   ✅ Grade calculator with rounding logic") 
message(STATUS "   ✅ 4 comprehensive test scenarios")
message(STATUS "   ✅ File system utilities")
message(STATUS "   ✅ Directory scanner with recursive search")
message(STATUS "   ✅ Excel file filtering with statistics")
if(LIBXLS_FOUND)
    message(STATUS "   ✅ libxls integration for Excel parsing")
else()
    message(STATUS "   ⚠️  libxls not available - Excel parsing disabled")
endif()
message(STATUS "")