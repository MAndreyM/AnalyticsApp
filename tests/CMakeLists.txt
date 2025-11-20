# tests/CMakeLists.txt
find_package(doctest REQUIRED)

# Тесты для Logger
add_executable(test_logger test_logger.cpp)
target_link_libraries(test_logger Utils doctest::doctest)

# Добавление в CTest
add_test(NAME LoggerTests COMMAND test_logger)
