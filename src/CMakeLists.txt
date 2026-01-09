# ============================================
# Файл: src/CMakeLists.txt
# Подкаталог исходного кода проекта
# ============================================

message(STATUS "Конфигурация исходного кода в: ${CMAKE_CURRENT_SOURCE_DIR}")

# ============================================
# 1. НАСТРОЙКА ПУТЕЙ И КАТАЛОГОВ
# ============================================

# Корневая директория исходников
set(SRC_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

# Директории подмодулей
set(CORE_DIR ${SRC_ROOT}/core)
set(PARSERS_DIR ${SRC_ROOT}/parsers)
set(SERVICES_DIR ${SRC_ROOT}/services)
set(CONTROLLERS_DIR ${SRC_ROOT}/controllers)
set(VIEWS_DIR ${SRC_ROOT}/views)

# Проверка существования директорий
foreach(dir ${CORE_DIR} ${PARSERS_DIR} ${SERVICES_DIR} ${CONTROLLERS_DIR} ${VIEWS_DIR})
    if(NOT EXISTS ${dir})
        message(WARNING "Директория не найдена: ${dir}")
    endif()
endforeach()

# ============================================
# 2. ПОИСК ИСХОДНЫХ ФАЙЛОВ
# ============================================

# Функция для поиска исходных файлов в директории
function(find_source_files VAR_NAME DIR)
    file(GLOB_RECURSE SOURCES
        "${DIR}/*.cpp"
        "${DIR}/*.cxx"
        "${DIR}/*.cc"
    )
    
    file(GLOB_RECURSE HEADERS
        "${DIR}/*.hpp"
        "${DIR}/*.h"
        "${DIR}/*.hxx"
    )
    
    file(GLOB_RECURSE UI_FILES
        "${DIR}/*.ui"
    )
    
    file(GLOB_RECURSE QRC_FILES
        "${DIR}/*.qrc"
    )
    
    # Устанавливаем переменную в родительской области видимости
    set(${VAR_NAME}_SOURCES ${SOURCES} PARENT_SCOPE)
    set(${VAR_NAME}_HEADERS ${HEADERS} PARENT_SCOPE)
    set(${VAR_NAME}_UI ${UI_FILES} PARENT_SCOPE)
    set(${VAR_NAME}_QRC ${QRC_FILES} PARENT_SCOPE)
endfunction()

# Поиск файлов для каждого модуля
find_source_files(CORE ${CORE_DIR})
find_source_files(PARSERS ${PARSERS_DIR})
find_source_files(SERVICES ${SERVICES_DIR})
find_source_files(CONTROLLERS ${CONTROLLERS_DIR})
find_source_files(VIEWS ${VIEWS_DIR})

# Главный файл приложения
set(APP_SOURCES "${SRC_ROOT}/main.cpp")

# ============================================
# 3. СОЗДАНИЕ БИБЛИОТЕК ПРОЕКТА
# ============================================

# 3.1. AnalyticsCore - ядро системы (базовые структуры данных)
add_library(AnalyticsCore STATIC
    ${CORE_SOURCES}
    ${CORE_HEADERS}
)

target_include_directories(AnalyticsCore PUBLIC
    $<BUILD_INTERFACE:${CORE_DIR}>
    $<INSTALL_INTERFACE:include/core>
)

target_compile_definitions(AnalyticsCore PRIVATE
    ANALYTICS_CORE_LIBRARY
)

message(STATUS "  AnalyticsCore: ${CORE_SOURCES}")

# 3.2. AnalyticsParsers - парсеры HTML файлов
add_library(AnalyticsParsers STATIC
    ${PARSERS_SOURCES}
    ${PARSERS_HEADERS}
)

target_include_directories(AnalyticsParsers PUBLIC
    $<BUILD_INTERFACE:${PARSERS_DIR}>
    $<BUILD_INTERFACE:${CORE_DIR}>  # Для структур данных
    $<INSTALL_INTERFACE:include/parsers>
)

target_link_libraries(AnalyticsParsers PUBLIC
    Qt6::Core
    Qt6::Xml
    AnalyticsCore  # Зависимость от ядра
)

target_compile_definitions(AnalyticsParsers PRIVATE
    ANALYTICS_PARSERS_LIBRARY
)

message(STATUS "  AnalyticsParsers: ${PARSERS_SOURCES}")

# 3.3. AnalyticsServices - сервисы (бизнес-логика)
add_library(AnalyticsServices STATIC
    ${SERVICES_SOURCES}
    ${SERVICES_HEADERS}
)

target_include_directories(AnalyticsServices PUBLIC
    $<BUILD_INTERFACE:${SERVICES_DIR}>
    $<BUILD_INTERFACE:${CORE_DIR}>  # Для структур данных
    $<INSTALL_INTERFACE:include/services>
)

target_link_libraries(AnalyticsServices PUBLIC
    AnalyticsCore  # Зависимость от ядра
)

target_compile_definitions(AnalyticsServices PRIVATE
    ANALYTICS_SERVICES_LIBRARY
)

message(STATUS "  AnalyticsServices: ${SERVICES_SOURCES}")

# 3.4. AnalyticsControllers - контроллеры (MVC паттерн)
add_library(AnalyticsControllers STATIC
    ${CONTROLLERS_SOURCES}
    ${CONTROLLERS_HEADERS}
)

target_include_directories(AnalyticsControllers PUBLIC
    $<BUILD_INTERFACE:${CONTROLLERS_DIR}>
    $<BUILD_INTERFACE:${CORE_DIR}>      # Для ViewModel
    $<BUILD_INTERFACE:${SERVICES_DIR}>  # Для сервисов
    $<BUILD_INTERFACE:${PARSERS_DIR}>   # Для парсеров
    $<INSTALL_INTERFACE:include/controllers>
)

target_link_libraries(AnalyticsControllers PUBLIC
    Qt6::Core           # Для сигналов/слотов
    AnalyticsCore       # Базовые структуры
    AnalyticsServices   # Сервисы
    AnalyticsParsers    # Парсеры
)

target_compile_definitions(AnalyticsControllers PRIVATE
    ANALYTICS_CONTROLLERS_LIBRARY
)

message(STATUS "  AnalyticsControllers: ${CONTROLLERS_SOURCES}")

# 3.5. AnalyticsViews - графический интерфейс
add_library(AnalyticsViews STATIC
    ${VIEWS_SOURCES}
    ${VIEWS_HEADERS}
    ${VIEWS_UI}
    ${VIEWS_QRC}
)

target_include_directories(AnalyticsViews PUBLIC
    $<BUILD_INTERFACE:${VIEWS_DIR}>
    $<BUILD_INTERFACE:${CORE_DIR}>        # Для ViewModel
    $<BUILD_INTERFACE:${CONTROLLERS_DIR}> # Для MainController
    $<INSTALL_INTERFACE:include/views>
)

target_link_libraries(AnalyticsViews PUBLIC
    Qt6::Core
    Qt6::Widgets
    AnalyticsCore       # ViewModel
    AnalyticsControllers # MainController
)

target_compile_definitions(AnalyticsViews PRIVATE
    ANALYTICS_VIEWS_LIBRARY
)

message(STATUS "  AnalyticsViews: ${VIEWS_SOURCES}")
if(VIEWS_UI)
    message(STATUS "    UI файлы: ${VIEWS_UI}")
endif()

# ============================================
# 4. СОЗДАНИЕ ИСПОЛНЯЕМОГО ФАЙЛА
# ============================================

add_executable(AnalyticsApp
    ${APP_SOURCES}
)

# Включаем директории для всех библиотек
target_include_directories(AnalyticsApp PRIVATE
    ${CORE_DIR}
    ${PARSERS_DIR}
    ${SERVICES_DIR}
    ${CONTROLLERS_DIR}
    ${VIEWS_DIR}
)

# Связываем все библиотеки с приложением
target_link_libraries(AnalyticsApp PRIVATE
    AnalyticsViews       # GUI
    AnalyticsControllers # Логика
    AnalyticsServices    # Сервисы
    AnalyticsParsers     # Парсеры
    AnalyticsCore        # Данные
    Qt6::Core
    Qt6::Widgets
    Qt6::Xml
)

# Установка свойств приложения
set_target_properties(AnalyticsApp PROPERTIES
    OUTPUT_NAME "analytics-app"
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE FALSE
)

if(WIN32)
    # Для Windows добавляем манифест
    set_target_properties(AnalyticsApp PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()

message(STATUS "  AnalyticsApp: ${APP_SOURCES}")

# ============================================
# 5. ПРОВЕРКА И ИНФОРМАЦИЯ
# ============================================

# Подсчет файлов
set(TOTAL_SOURCES 0)
set(TOTAL_HEADERS 0)

foreach(module CORE PARSERS SERVICES CONTROLLERS VIEWS)
    list(LENGTH ${module}_SOURCES module_sources)
    list(LENGTH ${module}_HEADERS module_headers)
    
    math(EXPR TOTAL_SOURCES "${TOTAL_SOURCES} + ${module_sources}")
    math(EXPR TOTAL_HEADERS "${TOTAL_HEADERS} + ${module_headers}")
    
    message(STATUS "  ${module}: ${module_sources} исходных, ${module_headers} заголовочных файлов")
endforeach()

message(STATUS "Всего исходных файлов: ${TOTAL_SOURCES}")
message(STATUS "Всего заголовочных файлов: ${TOTAL_HEADERS}")

# Проверка, что все цели созданы
set(ALL_TARGETS AnalyticsCore AnalyticsParsers AnalyticsServices AnalyticsControllers AnalyticsViews AnalyticsApp)

foreach(target ${ALL_TARGETS})
    if(TARGET ${target})
        message(STATUS "Цель создана: ${target}")
    else()
        message(FATAL_ERROR "Не удалось создать цель: ${target}")
    endif()
endforeach()

message(STATUS "Все цели проекта успешно созданы в src/CMakeLists.txt")

# ============================================
# 6. НАСТРОЙКА ПУБЛИЧНЫХ ИНТЕРФЕЙСОВ
# ============================================

# Создаем псевдоцель для всех библиотек
add_library(AnalyticsLibraries INTERFACE)
target_link_libraries(AnalyticsLibraries INTERFACE
    AnalyticsCore
    AnalyticsParsers
    AnalyticsServices
    AnalyticsControllers
    AnalyticsViews
)

# Экспорт целей для использования в других проектах
install(TARGETS
    AnalyticsCore
    AnalyticsParsers
    AnalyticsServices
    AnalyticsControllers
    AnalyticsViews
    AnalyticsApp
    EXPORT AnalyticsTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Экспорт конфигурационного файла
install(EXPORT AnalyticsTargets
    FILE AnalyticsTargets.cmake
    NAMESPACE Analytics::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/AnalyticsApp
)