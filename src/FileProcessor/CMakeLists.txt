# FileProcessor Module CMake Configuration
# ==========================================

set(FILE_PROCESSOR_SOURCES
    ExcelFileFilter.cpp
    DirectoryScanner.cpp
)

# Create FileProcessor library
add_library(FileProcessor ${FILE_PROCESSOR_SOURCES})

# Include directories
target_include_directories(FileProcessor 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/..
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

# Installation configuration (if needed)
install(TARGETS FileProcessor
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

message(STATUS "FileProcessor module configured")