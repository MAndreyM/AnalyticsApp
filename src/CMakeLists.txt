cmake_minimum_required(VERSION 3.16)

# ============================================================================
# ПОДКЛЮЧЕНИЕ ПОДМОДУЛЕЙ
# ============================================================================

# Подключаем модули в правильном порядке зависимостей
add_subdirectory(Utils)          # Базовые утилиты
add_subdirectory(DataProcessor)  # Модели данных и анализ
add_subdirectory(FileProcessor)  # Обработка файлов (зависит от Utils)

# ============================================================================
# ОСНОВНОЕ ПРИЛОЖЕНИЕ
# ============================================================================

add_executable(analytics_app main.cpp)

# Связываем все модули с основным приложением
target_link_libraries(analytics_app 
    PRIVATE 
        DataProcessor
        Utils
        FileProcessor
)

# Устанавливаем выходную директорию
set_target_properties(analytics_app 
    PROPERTIES 
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# ============================================================================
# ДЕМО-ПРОГРАММЫ
# ============================================================================

# Демо-программа для моделей данных
add_executable(demo_datamodels demo_datamodels.cpp)
target_link_libraries(demo_datamodels 
    PRIVATE 
        DataProcessor
        Utils
)
set_target_properties(demo_datamodels 
    PROPERTIES 
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Демо-программа для сканирования директорий
add_executable(demo_directory_scanner demo_directory_scanner.cpp)
target_link_libraries(demo_directory_scanner 
    PRIVATE 
        DataProcessor
        Utils
        FileProcessor
)
set_target_properties(demo_directory_scanner 
    PROPERTIES 
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# ============================================================================
# НАСТРОЙКИ КОМПИЛЯЦИИ
# ============================================================================

# Глобальные настройки компилятора
if(MSVC)
    target_compile_options(analytics_app PRIVATE /W4)
    target_compile_options(demo_datamodels PRIVATE /W4)
    target_compile_options(demo_directory_scanner PRIVATE /W4)
else()
    target_compile_options(analytics_app PRIVATE -Wall -Wextra)
    target_compile_options(demo_datamodels PRIVATE -Wall -Wextra)
    target_compile_options(demo_directory_scanner PRIVATE -Wall -Wextra)
endif()

# Стандарт C++
target_compile_features(analytics_app PUBLIC cxx_std_20)
target_compile_features(demo_datamodels PUBLIC cxx_std_20)
target_compile_features(demo_directory_scanner PUBLIC cxx_std_20)

# ============================================================================
# ИНФОРМАЦИЯ О СБОРКЕ
# ============================================================================

message(STATUS "")
message(STATUS "🎯 AnalyticsApp Configuration Complete")
message(STATUS "   Version: 0.1.0")
message(STATUS "   C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "   Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "")
message(STATUS "📦 Available Targets:")
message(STATUS "   analytics_app         - Main application")
message(STATUS "   demo_datamodels       - Data models demonstration")
message(STATUS "   demo_directory_scanner - Directory scanner demonstration")
message(STATUS "")
message(STATUS "🏗️  Project Structure:")
message(STATUS "   src/DataProcessor/    - Data models and analysis logic")
message(STATUS "   src/Utils/            - File system utilities")
message(STATUS "   src/FileProcessor/    - Directory scanning and file processing")
message(STATUS "")
message(STATUS "🚀 Current Features:")
message(STATUS "   ✅ Data models with validation")
message(STATUS "   ✅ Grade calculator with rounding logic")
message(STATUS "   ✅ File system utilities")
message(STATUS "   ✅ Directory scanner with recursive search")
message(STATUS "   ✅ Excel file filtering with statistics")
message(STATUS "   ✅ 4 comprehensive test scenarios")
message(STATUS "")