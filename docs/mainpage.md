/*!
\mainpage Analytics App - Документация API
\tableofcontents

\section intro_sec Введение

**Analytics App** - кроссплатформенное приложение для анализа успеваемости учащихся 
на основе данных из файлов Excel.

**Версия 0.1.0** представляет собой базовый каркас проекта с полной системой тестирования.

\section features_sec Основные возможности Phase 2

\subsection analysis_sec 📊 Анализ данных
- Модели данных Student и AnalysisResult с валидацией
- GradeCalculator с логикой округления оценок
- 4 комплексных тестовых сценария анализа успеваемости

\subsection testing_sec 🧪 Тестирование
- Unit-тесты для всех основных компонентов
- Интеграционные тесты для 4 сценариев
- Автоматическая проверка на CI/CD

\subsection utils_sec 🔧 Утилиты
- FileSystemUtils для кроссплатформенных операций
- StringUtils для работы со строками
- Обработка ошибок и валидация данных

\section quick_start_sec Быстрый старт

\subsection build_sec Сборка проекта
\code{.bash}
# Клонирование репозитория
git clone https://github.com/MAndreyM/AnalyticsApp.git
cd AnalyticsApp

# Полная проверка Phase 2
./scripts/test_phase2.sh

# Или ручная сборка
mkdir build && cd build
cmake -G Ninja ..
ninja
\endcode

\subsection demo_sec Демонстрация
\code{.bash}
# Запуск демонстрационной программы
./bin/demo_datamodels

# Формат вывода:
# ------
# Класс
# предмет <-> ФИО
# ------
# Класс  
# предмет <-> ФИО
\endcode

\section architecture_sec Архитектура

\subsection modules_sec Основные модули

\subsubsection dataprocessor_sec DataProcessor
- \ref Student - модель данных учащегося
- \ref GradeCalculator - анализ успеваемости
- \ref AnalysisResult - хранение результатов

\subsubsection utils_sec Utils
- \ref FileSystemUtils - работа с файловой системой
- \ref StringUtils - обработка строк

\subsection business_logic_sec Бизнес-логика

\subsubsection grading_sec Округление оценок
Правила округления средних баллов:
- Дробная часть ≥ 0.6 → округление в большую сторону
- Дробная часть < 0.6 → округление в меньшую сторону

Примеры:
- 3.6 → 4, 3.75 → 4, 4.55 → 4, 2.3 → 2

\subsubsection criteria_sec Критерии анализа
- **Одна тройка**: только одна оценка "3" среди всех предметов
- **Нулевой балл**: хотя бы один средний балл равен 0.0

\section api_sec API Reference

\subsection classes_sec Основные классы

| Класс | Назначение |
|-------|------------|
| \ref Student | Модель данных учащегося с валидацией |
| \ref GradeCalculator | Калькулятор оценок и анализа |
| \ref AnalysisResult | Результаты анализа успеваемости |
| \ref FileSystemUtils | Утилиты файловой системы |
| \ref StringUtils | Утилиты для работы со строками |

\subsection example_sec Пример использования
\code{.cpp}
// Создание студента
Student student("10A", "Иванов Иван Иванович");
student.addSubjectScore("Математика", 4.5);
student.addSubjectScore("Физика", 3.6);

// Анализ успеваемости
GradeCalculator calculator;
calculator.calculateAllGrades(student);

bool hasSingleThree = calculator.hasSingleThree(student);
bool hasZeroScore = calculator.hasZeroScore(student);
\endcode

\section testing_sec Тестирование

\subsection scenarios_sec Тестовые сценарии
Проект включает 4 комплексных сценария:

1. **Класс без одной тройки и без нулевых баллов**
2. **Класс с одной тройкой и двумя тройками**
3. **Класс с нулевыми баллами**  
4. **Класс с одной тройкой и нулевыми баллами**

\subsection running_tests_sec Запуск тестов
\code{.bash}
# Все unit-тесты
./test_datamodels
./test_gradecalculator
./test_filesystem

# Через CTest
ctest -L unit_tests
\endcode

\section development_sec Разработка

\subsection git_flow_sec Git Flow
- `main` - стабильные версии
- `develop` - текущая разработка  
- `feature/*` - новые функции

\subsection ci_cd_sec CI/CD
- Автоматическая сборка на RedOS, Alt Linux, Windows
- Запуск всех unit-тестов
- Проверка формата вывода демо-программы

\section license_sec Лицензия

Проект распространяется под лицензией **MIT**.

\copyright 2024 MAndreyM

\see https://github.com/MAndreyM/AnalyticsApp
\see README.md для инструкций по сборке и использованию
*/