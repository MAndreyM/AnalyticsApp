# ============================================================================
# DataProcessor MODULE
# ============================================================================

# Библиотека обработки данных
add_library(DataProcessor
    DataModels.cpp
    # В будущем добавим:
    # GradeCalculator.cpp
    # StudentAnalyzer.cpp
)

# Публичные include директории
target_include_directories(DataProcessor PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Настройка компиляции
target_compile_features(DataProcessor PRIVATE cxx_std_20)

if(MSVC)
    target_compile_options(DataProcessor PRIVATE /W4 /permissive-)
else()
    target_compile_options(DataProcessor PRIVATE -Wall -Wextra -Wpedantic)
endif()