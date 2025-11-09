/*!
\mainpage Analytics App - Документация
\tableofcontents

\section intro_sec Введение

**Analytics App** - кроссплатформенное приложение для анализа успеваемости учащихся 
на основе данных из файлов Excel.

Приложение предоставляет функциональность для:
- Автоматического анализа успеваемости учащихся
- Выявления учащихся с определенными характеристиками успеваемости  
- Генерации отчетов в формате XLSX

\section features_sec Основные возможности

\subsection analysis_sec 📊 Анализ данных
- Чтение и парсинг XLS-файлов
- Расчет средних баллов и оценок
- Фильтрация учащихся по критериям

\subsection reports_sec 📈 Генерация отчетов
- Отчет об учащихся с одной тройкой
- Отчет об учащихся с нулевым баллом
- Группировка по классам

\subsection crossplatform_sec 🌐 Кроссплатформенность
- **RedOS** - российская ОС
- **Alt Linux** - российский дистрибутив
- **Windows** - поддержка MSVC

\section quick_start_sec Быстрый старт

\subsection build_sec Сборка проекта
\code{.bash}
git clone https://github.com/MAndreyM/AnalyticsApp.git
cd AnalyticsApp
mkdir build && cd build
cmake -G Ninja ..
ninja
\endcode

\subsection usage_sec Использование
\code{.bash}
# Базовое использование
./analytics_app /path/to/data

# Подробный вывод
./analytics_app -v /path/to/data

# Указание выходной директории
./analytics_app -o ./reports /path/to/data
\endcode

\section architecture_sec Архитектура

\subsection modules_sec Основные модули

\subsubsection file_processor Модуль работы с файлами
- DirectoryScanner - поиск Excel файлов
- ExcelParser - парсинг данных учащихся
- ReportGenerator - генерация отчетов

\subsubsection data_processor Модуль обработки данных  
- Student - модель данных учащегося
- GradeCalculator - расчет оценок
- StudentAnalyzer - анализ успеваемости

\subsubsection utils_sec Вспомогательные модули
- Logger - система логирования
- CommandLineParser - обработка аргументов CLI

\section api_sec API Reference

\subsection classes_sec Основные классы

| Класс | Назначение |
|-------|------------|
| CommandLineParser | Разбор аргументов командной строки |
| Logger | Логирование сообщений приложения |
| DirectoryScanner | Поиск Excel файлов в директории |
| Student | Модель данных учащегося |

\subsection example_sec Пример использования Logger
\code{.cpp}
Logger logger(true); // verbose mode enabled
logger.info("Application started");
logger.debug("Debug information");
logger.error("Error message");
\endcode

\section development_sec Разработка

\subsection git_flow Git Flow
Проект использует упрощенный Git Flow:
- `main` - стабильные версии
- `develop` - текущая разработка
- `feature/*` - новые функции

\subsection commits_sec Коммиты
- `WIP:` - черновая работа
- `PROGRES:` - значительный прогресс
- `FEAT:` - завершенная функциональность
- `FIX:` - исправления ошибок
- `DOCS:` - документация

\section license_sec Лицензия

Проект распространяется под лицензией **MIT**.

\copyright 2024 MAndreyM

\see https://github.com/MAndreyM/AnalyticsApp
\see README.md для инструкций по сборке и использованию
*/