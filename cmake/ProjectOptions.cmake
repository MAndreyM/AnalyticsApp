# ============================================
# Файл: cmake/ProjectOptions.cmake
# ============================================

# Настройка опций проекта
function(setup_project_options)
    # Основные опции проекта
    option(BUILD_SHARED_LIBS "Сборка динамических библиотек" OFF)
    option(BUILD_TESTING "Включение тестов" ON)
    option(ENABLE_COVERAGE "Включение покрытия кода" OFF)
    option(ENABLE_SANITIZERS "Включение санитайзеров" OFF)
    option(WARNINGS_AS_ERRORS "Предупреждения как ошибки" ON)
    
    # Опции для разработки
    option(ENABLE_CCACHE "Использование ccache для ускорения сборки" ON)
    option(ENABLE_IPO "Включение межпроцедурной оптимизации" OFF)
    
    # Вывод информации об опциях
    message(STATUS "Настройки проекта:")
    message(STATUS "  BUILD_SHARED_LIBS: ${BUILD_SHARED_LIBS}")
    message(STATUS "  BUILD_TESTING: ${BUILD_TESTING}")
    message(STATUS "  WARNINGS_AS_ERRORS: ${WARNINGS_AS_ERRORS}")
    
    # Настройка ccache
    if(ENABLE_CCACHE)
        find_program(CCACHE_PROGRAM ccache)
        if(CCACHE_PROGRAM)
            set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
            message(STATUS "Используется ccache для ускорения сборки")
        else()
            message(WARNING "ccache не найден, сборка может быть медленнее")
        endif()
    endif()
    
    # Настройка межпроцедурной оптимизации
    if(ENABLE_IPO)
        include(CheckIPOSupported)
        check_ipo_supported(RESULT IPO_SUPPORTED OUTPUT IPO_OUTPUT)
        if(IPO_SUPPORTED)
            set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
            message(STATUS "Межпроцедурная оптимизация включена")
        else()
            message(WARNING "Межпроцедурная оптимизация не поддерживается: ${IPO_OUTPUT}")
        endif()
    endif()
endfunction()