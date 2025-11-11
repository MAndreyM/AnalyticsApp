# ============================================================================
# ТЕСТИРОВАНИЕ
# ============================================================================

message(STATUS "Configuring tests...")

# Простой способ для header-only библиотеки
include(FetchContent)
FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG v2.4.11
)

# Получаем контент без автоматического add_subdirectory()
FetchContent_GetProperties(doctest)
if(NOT doctest_POPULATED)
    FetchContent_Populate(doctest)
    # Создаем интерфейсную библиотеку вместо использования их CMakeLists.txt
    add_library(doctest INTERFACE)
    target_include_directories(doctest INTERFACE ${doctest_SOURCE_DIR})
    target_compile_definitions(doctest INTERFACE DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN)
endif()

# ============================================================================
# СУЩЕСТВУЮЩИЕ ТЕСТЫ
# ============================================================================

# Тесты для моделей данных
add_executable(test_datamodels test_datamodels.cpp)
target_link_libraries(test_datamodels 
    PRIVATE 
        DataProcessor 
        Utils
        doctest
)
target_include_directories(test_datamodels PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Тесты для калькулятора оценок
add_executable(test_gradecalculator test_gradecalculator.cpp)
target_link_libraries(test_gradecalculator 
    PRIVATE 
        DataProcessor 
        Utils
        doctest
)
target_include_directories(test_gradecalculator PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Тесты для утилит файловой системы
add_executable(test_filesystem test_filesystem.cpp)
target_link_libraries(test_filesystem 
    PRIVATE 
        DataProcessor 
        Utils 
        doctest
)
target_include_directories(test_filesystem PRIVATE ${CMAKE_SOURCE_DIR}/src)

# ============================================================================
# НОВЫЕ ТЕСТЫ ДЛЯ DIRECTORY SCANNER
# ============================================================================

# Тесты для DirectoryScanner
add_executable(test_directory_scanner test_directory_scanner.cpp)
target_link_libraries(test_directory_scanner 
    PRIVATE 
        DataProcessor 
        Utils 
        FileProcessor
        doctest
)
target_include_directories(test_directory_scanner PRIVATE ${CMAKE_SOURCE_DIR}/src)

# ============================================================================
# НАСТРОЙКА ВЫХОДНЫХ ДИРЕКТОРИЙ
# ============================================================================

set_target_properties(
    test_datamodels 
    test_gradecalculator
    test_filesystem
    test_directory_scanner
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

# ============================================================================
# ДОБАВЛЕНИЕ ТЕСТОВ В CTEST
# ============================================================================

add_test(NAME DataModelsTests COMMAND test_datamodels)
add_test(NAME GradeCalculatorTests COMMAND test_gradecalculator)
add_test(NAME FileSystemTests COMMAND test_filesystem)
add_test(NAME DirectoryScannerTests COMMAND test_directory_scanner)

# Группируем тесты
set_tests_properties(
    DataModelsTests 
    GradeCalculatorTests
    FileSystemTests
    DirectoryScannerTests
    PROPERTIES 
    LABELS "unit_tests"
)

# ============================================================================
# ИНФОРМАЦИЯ О ТЕСТАХ
# ============================================================================

message(STATUS "  test_datamodels          - Data models unit tests")
message(STATUS "  test_gradecalculator     - Grade calculator (4 scenarios)")
message(STATUS "  test_filesystem          - File system utilities")
message(STATUS "  test_directory_scanner   - Directory scanner comprehensive tests")