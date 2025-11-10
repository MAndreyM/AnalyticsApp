# ============================================================================
# ТЕСТИРОВАНИЕ
# ============================================================================

# Простой способ для header-only библиотеки
include(FetchContent)
FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG v2.4.11
)
FetchContent_MakeAvailable(doctest)

# Для doctest нужно определить макрос, так как это header-only библиотека
target_compile_definitions(doctest INTERFACE DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN)

# Тесты для моделей данных
add_executable(test_datamodels test_datamodels.cpp)
target_link_libraries(test_datamodels DataProcessor doctest)
target_include_directories(test_datamodels PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Тесты для калькулятора оценок
add_executable(test_gradecalculator test_gradecalculator.cpp)
target_link_libraries(test_gradecalculator DataProcessor doctest)
target_include_directories(test_gradecalculator PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Настройка выходных директорий
set_target_properties(
    test_datamodels 
    test_gradecalculator
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Добавляем тесты в CTest
add_test(NAME DataModelsTests COMMAND test_datamodels)
add_test(NAME GradeCalculatorTests COMMAND test_gradecalculator)

# Группируем тесты
set_tests_properties(
    DataModelsTests 
    GradeCalculatorTests
    PROPERTIES 
    LABELS "unit_tests"
)

message(STATUS "Testing configuration complete")