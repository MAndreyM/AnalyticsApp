# ============================================
# Файл: tests/CMakeLists.txt
# Сборка тестов для проекта AnalyticsApp
# ============================================

message(STATUS "Настройка тестов...")

# 1. Создание исполняемого файла для тестов
add_executable(tests
    unit/test_doctest_integration.cpp
)

# 2. Подключение заголовочных файлов
target_include_directories(tests PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/third_party/doctest
)

# 3. Подключение библиотек проекта
target_link_libraries(tests PRIVATE
    AnalyticsCore
    AnalyticsParsers
    AnalyticsServices
    doctest
    Qt6::Core
    Qt6::Xml
)

# 4. Настройка свойств цели - ИЗМЕНЕНО: вывод в текущую директорию
set_target_properties(tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}  # Изменено!
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

# 5. Добавление цели для запуска тестов - ИЗМЕНЕНО путь к исполняемому файлу
add_custom_target(run_tests
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tests --success  # Изменено!
    DEPENDS tests
    COMMENT "Запуск тестов..."
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

# 6. Добавление цели для тестов с выводом подробной информации
add_custom_target(test_verbose
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tests --success --no-skip --no-exitcode  # Изменено!
    DEPENDS tests
    COMMENT "Запуск тестов с подробным выводом..."
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

# 7. Настройка покрытия кода (если поддерживается)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # Включение флагов для покрытия кода
    target_compile_options(tests PRIVATE --coverage)
    target_link_options(tests PRIVATE --coverage)
    
    message(STATUS "Покрытие кода включено для тестов")
endif()

message(STATUS "Тесты настроены успешно")
