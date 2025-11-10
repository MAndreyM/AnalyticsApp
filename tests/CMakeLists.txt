# ============================================================================
# ТЕСТИРОВАНИЕ
# ============================================================================

include(FetchContent)

FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG v2.4.11
)

FetchContent_MakeAvailable(doctest)

# Тесты для моделей данных
add_executable(test_datamodels test_datamodels.cpp)

# Добавляем include-директории (правильный путь к doctest)
target_include_directories(test_datamodels PRIVATE 
    ${doctest_SOURCE_DIR}  # Для #include <doctest/doctest.h>
    ${doctest_SOURCE_DIR}/doctest  # Для #include "doctest.h"  
    ${CMAKE_SOURCE_DIR}/src
)

# Линкуем только DataProcessor
target_link_libraries(test_datamodels PRIVATE DataProcessor)

# Настройка выходных директорий
set_target_properties(test_datamodels PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Добавляем тесты в CTest
add_test(NAME DataModelsTests COMMAND test_datamodels)