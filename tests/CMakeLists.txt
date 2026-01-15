# ============================================
# Файл: tests/CMakeLists.txt
# Сборка тестов для проекта AnalyticsApp
# ============================================

message(STATUS "Настройка тестов...")

# 1. Поиск файлов с тестами
file(GLOB_RECURSE TEST_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/unit/*.cpp"
)

# Исключаем ненужный файл интеграции
list(REMOVE_ITEM TEST_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/unit/test_doctest_integration.cpp"
)

# 2. Создаем main.cpp для тестов
set(TEST_MAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/test_main.cpp")

# Если файл main.cpp еще не существует, создадим его через CMake
#if(NOT EXISTS "${TEST_MAIN_FILE}")
#    file(WRITE "${TEST_MAIN_FILE}" 
#        "#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN\n"
#        "#include \"doctest.h\"\n"
#        "\n"
#        "// Главный файл для запуска всех тестов\n"
#        "// Реализация doctest находится только здесь\n"
#    )
#    message(STATUS "Создан файл main.cpp для тестов")
#endif()

# 3. Добавляем main.cpp в список исходников ПЕРВЫМ
list(INSERT TEST_SOURCES 0 "${TEST_MAIN_FILE}")

message(STATUS "Найдено тестовых файлов: ${TEST_SOURCES}")

# 4. Создание исполняемого файла для тестов
add_executable(tests
    ${TEST_SOURCES}
)

# 5. УДАЛЕНО: target_compile_definitions с DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
# Этот макрос теперь определен только в main.cpp

# 6. Подключение заголовочных файлов
target_include_directories(tests PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/third_party/doctest
    ${CMAKE_CURRENT_SOURCE_DIR}  # Для нахождения main.cpp
)

# 7. Подключение библиотек проекта
target_link_libraries(tests PRIVATE
    AnalyticsCore
    AnalyticsParsers
    AnalyticsServices
    AnalyticsControllers
    AnalyticsViews
    doctest
    Qt6::Core
    Qt6::Xml
)

# 8. Настройка свойств цели
set_target_properties(tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

# 9. Добавление цели для запуска тестов
add_custom_target(run_tests
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tests --success
    DEPENDS tests
    COMMENT "Запуск тестов..."
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

# 10. Добавление цели для тестов с выводом подробной информации
add_custom_target(test_verbose
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tests --success --no-skip --no-exitcode
    DEPENDS tests
    COMMENT "Запуск тестов с подробным выводом..."
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

# 11. Настройка покрытия кода (если поддерживается)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # Включение флагов для покрытия кода
    target_compile_options(tests PRIVATE --coverage)
    target_link_options(tests PRIVATE --coverage)
    
    message(STATUS "Покрытие кода включено для тестов")
endif()

message(STATUS "Тесты настроены успешно")