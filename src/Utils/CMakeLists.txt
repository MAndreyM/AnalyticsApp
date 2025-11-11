# Utils Module CMake Configuration
# =================================

set(UTILS_SOURCES
    FileSystemUtils.cpp
)

# Create Utils as OBJECT library
add_library(Utils OBJECT ${UTILS_SOURCES})

target_include_directories(Utils
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(Utils 
    PROPERTIES 
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

message(STATUS "Utils module configured - OBJECT library")