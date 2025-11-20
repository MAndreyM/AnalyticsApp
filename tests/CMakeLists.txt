# tests/CMakeLists.txt

# Для отдельных тестов - с DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
add_executable(test_config test_config.cpp)
target_link_libraries(test_config PRIVATE Utils doctest::doctest)
target_compile_definitions(test_config PRIVATE DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN)

add_executable(test_logger test_logger.cpp)  
target_link_libraries(test_logger PRIVATE Utils doctest::doctest)
target_compile_definitions(test_logger PRIVATE DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN)

# Для run_tests - с отдельным main.cpp (БЕЗ DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN в компиляции)
add_executable(run_tests
    main.cpp
    test_logger.cpp
    test_config.cpp
)
target_link_libraries(run_tests PRIVATE Utils doctest::doctest)

# Добавление в CTest
add_test(NAME LoggerTests COMMAND test_logger)
add_test(NAME ConfigTests COMMAND test_config)
add_test(NAME AllTests COMMAND run_tests)