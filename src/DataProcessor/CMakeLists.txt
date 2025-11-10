# ============================================================================
# DataProcessor MODULE
# ============================================================================

# Библиотека обработки данных
add_library(DataProcessor
    DataModels.cpp
    GradeCalculator.cpp  # ← ДОБАВЛЕНО
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

# Информация о модуле
message(STATUS "DataProcessor module configured")
message(STATUS "  Sources: DataModels.cpp, GradeCalculator.cpp")
message(STATUS "  Headers: DataModels.h, GradeCalculator.h")