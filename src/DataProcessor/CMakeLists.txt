# DataProcessor Module CMake Configuration
# ==========================================

set(DATA_PROCESSOR_SOURCES
    DataModels.cpp
    GradeCalculator.cpp
)

# Create DataProcessor as OBJECT library
add_library(DataProcessor OBJECT ${DATA_PROCESSOR_SOURCES})

target_include_directories(DataProcessor 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(DataProcessor 
    PROPERTIES 
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

message(STATUS "DataProcessor module configured - OBJECT library")