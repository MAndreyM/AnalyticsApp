# FileProcessor Module CMake Configuration
# ==========================================

set(FILE_PROCESSOR_SOURCES
    ExcelFileFilter.cpp
    DirectoryScanner.cpp
)

# Create FileProcessor as OBJECT library
add_library(FileProcessor OBJECT ${FILE_PROCESSOR_SOURCES})

# Include directories
target_include_directories(FileProcessor 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link dependencies
target_link_libraries(FileProcessor 
    PUBLIC 
        Utils
)

# Compiler specific settings
if(MSVC)
    target_compile_options(FileProcessor PRIVATE /W4)
else()
    target_compile_options(FileProcessor PRIVATE -Wall -Wextra)
endif()

# Set C++ standard
target_compile_features(FileProcessor PUBLIC cxx_std_20)

# Set output directories for object files
set_target_properties(FileProcessor 
    PROPERTIES 
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

message(STATUS "FileProcessor module configured - OBJECT library")