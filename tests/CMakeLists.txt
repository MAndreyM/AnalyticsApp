# tests/CMakeLists.txt
add_executable(test_config test_config.cpp)
target_link_libraries(test_config Utils doctest::doctest)

# Общий тестовый запуск
add_executable(run_tests
    test_logger.cpp
    test_config.cpp
)
target_link_libraries(run_tests Utils doctest::doctest)

# Добавление в CTest
add_test(NAME LoggerTests COMMAND test_logger)
add_test(NAME ConfigTests COMMAND test_config)
add_test(NAME AllTests COMMAND run_tests)