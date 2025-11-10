# ============================================================================
# КОРНЕВОЙ CMakeLists.txt ДЛЯ src КАТАЛОГА
# ============================================================================

message(STATUS "Configuring source directory...")

# Основное приложение
add_executable(analytics_app main.cpp)

# Демонстрационная программа
add_executable(demo_datamodels demo_datamodels.cpp)

# Подключаем поддиректории
add_subdirectory(DataProcessor)
add_subdirectory(Utils)

# Линкуем основные библиотеки
target_link_libraries(analytics_app DataProcessor Utils)
target_link_libraries(demo_datamodels DataProcessor Utils)

set_target_properties(
    analytics_app
    demo_datamodels
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Информация о приложениях
message(STATUS "  analytics_app    - Main CLI application")
message(STATUS "  demo_datamodels  - Phase 2 demonstration")