# ============================================================================
# UTILS MODULE
# ============================================================================

message(STATUS "Configuring Utils module...")

# Библиотека утилит
add_library(Utils
    FileSystemUtils.cpp
)

# Публичные include директории
target_include_directories(Utils PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Настройка компиляции
target_compile_features(Utils PRIVATE cxx_std_20)

if(MSVC)
    target_compile_options(Utils PRIVATE /W4 /permissive-)
else()
    target_compile_options(Utils PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Информация о модуле
message(STATUS "  Utils            - File system utilities") 
message(STATUS "    Sources: FileSystemUtils.cpp")
message(STATUS "    Headers: FileSystemUtils.h")
message(STATUS "    Dependencies: std::filesystem")