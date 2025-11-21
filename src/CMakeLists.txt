# Основное приложение
add_executable(analytics_app main.cpp)

# Демонстрационная программа
add_executable(demo_html_parser Demo/demo_html_parser.cpp)

# Утилиты
add_library(Utils
    Utils/Logger.cpp
    Utils/Config.cpp
    Core/DataModels.cpp  # ← ДОБАВЛЕНО
)

# Подключение зависимостей
target_link_libraries(analytics_app Utils)
target_link_libraries(demo_html_parser Utils)