# ============================================
# Файл: cmake/PlatformSetup.cmake
# ============================================

# Настройка платформо-зависимых параметров
function(setup_platform)
    if(TARGET_OS STREQUAL "linux")
        # Настройки для Linux/RedOS
        set(LINUX TRUE PARENT_SCOPE)
        
        # Пути для RedOS
        if(EXISTS "/etc/redhat-release")
            message(STATUS "Обнаружена RedOS")
            set(REDOS TRUE PARENT_SCOPE)
            
            # Стандартные пути для RedOS 7.x
            list(APPEND CMAKE_PREFIX_PATH "/usr/lib64/qt6")
            list(APPEND CMAKE_PREFIX_PATH "/usr/local/qt6")
        endif()
        
    elseif(TARGET_OS STREQUAL "windows")
        # Настройки для Windows
        set(WINDOWS TRUE PARENT_SCOPE)
        
        # Настройки путей для Windows
        set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON PARENT_SCOPE)
        
        # Для MSVC
        if(MSVC)
            # Отключение предупреждений для безопасных функций
            add_definitions(-D_CRT_SECURE_NO_WARNINGS)
            add_definitions(-D_SCL_SECURE_NO_WARNINGS)
        endif()
    endif()
endfunction()