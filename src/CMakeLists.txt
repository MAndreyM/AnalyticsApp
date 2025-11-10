# ============================================================================
# КОРНЕВОЙ CMakeLists.txt ДЛЯ src КАТАЛОГА
# ============================================================================

# Основное приложение
add_executable(analytics_app main.cpp)

# Подключаем поддиректории
add_subdirectory(DataProcessor)
# В будущем добавим:
# add_subdirectory(FileProcessor)
add_subdirectory(Utils)

# Линкуем основные библиотеки
target_link_libraries(analytics_app DataProcessor Utils)

set_target_properties(
    analytics_app
    #demo_datamodels
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Информация о приложениях
message(STATUS "Applications configured:")
message(STATUS "  analytics_app - Main application")