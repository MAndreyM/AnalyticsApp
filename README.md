# Analytics App - Анализ успеваемости учащихся

## 📊 CI/CD Status

| Ветка | Статус | Платформы |
|-------|--------|-----------|
| Feature Branches | ![Feature CI](https://github.com/MAndreyM/AnalyticsApp/actions/workflows/ci-feature.yaml/badge.svg) | RedOS, Alt Linux, Windows |
| Develop Branch | ![Develop CI](https://github.com/MAndreyM/AnalyticsApp/actions/workflows/ci-main.yaml/badge.svg?branch=develop) | Продакшен сборка |
| Main Branch | ![Main CI](https://github.com/MAndreyM/AnalyticsApp/actions/workflows/ci-main.yaml/badge.svg?branch=main) | Стабильная версия |

## 🚀 О проекте
Кроссплатформенное CLI приложение для анализа успеваемости учащихся на основе данных из Excel файлов.

## 🏷️ Версия 0.1.0 - "Базовый каркас с тестированием"

### Что нового в версии 0.1.0:
- ✅ **Базовая структура проекта** с CMake и Ninja
- ✅ **Модели данных** с валидацией (Student, AnalysisResult)
- ✅ **Калькулятор оценок** с правилами округления
- ✅ **4 комплексных тестовых сценария** анализа успеваемости
- ✅ **Демонстрационная программа** с выводом в требуемом формате
- ✅ **Полная система тестирования** (doctest)
- ✅ **Валидация данных** и обработка ошибок
- ✅ **Утилиты файловой системы** для кроссплатформенных операций
- ✅ **Документация** Doxygen
- ✅ **Кроссплатформенная сборка** (RedOS, Alt Linux, Windows)

## 📋 Поддерживаемые платформы

- ✅ **RedOS** - основная целевая платформа
- ✅ **Alt Linux Latest** - актуальная версия
- ✅ **Alt Linux 10** - стабильная версия  
- ✅ **Windows** - поддержка MSVC

## 🧪 Тестирование и демонстрация

### Тестовые сценарии
Приложение включает 4 комплексных тестовых сценария:

1. **Класс без одной тройки и без нулевых баллов**
2. **Класс с одной тройкой и двумя тройками**  
3. **Класс с нулевыми баллами**
4. **Класс с одной тройкой и нулевыми баллами**

### Формат вывода
Демонстрационная программа выводит результаты в формате:

```text
------
Класс
предмет <-> ФИО
предмет <-> ФИО
------
Класс
предмет <-> ФИО
```

### Запуск тестов и демо
```bash
# Сборка проекта
mkdir build && cd build
cmake -G Ninja ..
ninja

# Запуск unit-тестов
./test_datamodels
./test_gradecalculator
./test_filesystem

# Запуск демонстрационной программы
./bin/demo_datamodels

# Основное приложение
./bin/analytics_app --help
```

## 🐳 Используемые Docker образы

Для CI/CD используются предварительно собранные Docker образы:

```bash
# RedOS CI образ
docker pull mandrm/redos-ci-analytics:latest

# Alt Linux образы
docker pull mandrm/altlinux-ci-analytics:latest
docker pull mandrm/altlinux-ci-analytics:alt10

# Локальное тестирование на RedOS
docker run --rm -v $(pwd):/workspace mandrm/redos-ci-analytics:latest \
  bash -c "mkdir build && cd build && cmake -G Ninja .. && ninja"

# Локальное тестирование на Alt Linux
docker run --rm -v $(pwd):/workspace mandrm/altlinux-ci-analytics:latest \
  bash -c "mkdir build && cd build && cmake -G Ninja .. && ninja"
```

## 🛠 Сборка и запуск

### Требования

- CMake ≥ 3.16
- Ninja
- C++20 компилятор (GCC, Clang, MSVC)
- doctest (для тестирования)

### Быстрый старт

```bash
git clone https://github.com/MAndreyM/AnalyticsApp.git
cd AnalyticsApp

# Полная проверка Phase 2
./scripts/test_phase2.sh

# Или вручную
mkdir build && cd build
cmake -G Ninja ..
ninja

# Тестирование
./test_datamodels
./test_gradecalculator
./test_filesystem

# Демонстрация
./bin/demo_datamodels
```

### RedOS / Alt Linux

```bash
git clone https://github.com/MAndreyM/AnalyticsApp.git
cd AnalyticsApp
mkdir build && cd build
cmake -G Ninja ..
ninja
./bin/analytics_app --help
```

### Windows

```cmd
git clone https://github.com/MAndreyM/AnalyticsApp.git
cd AnalyticsApp
build.bat
build\bin\analytics_app.exe --help
```

### Проверка сборки

```bash
./scripts/ci_setup.sh  # Linux
scripts\verify_build.bat  # Windows
```

## 🎯 Использование

```bash
./analytics_app [OPTIONS] INPUT_DIRECTORY

Options:
  -o, --output DIR   Output directory for reports (default: current dir)
  -v, --verbose      Enable verbose output
  -h, --help         Show this help message

Examples:
  ./analytics_app /path/to/data
  ./analytics_app -v -o ./reports /path/to/data
```

## 📊 Архитектура Phase 2

### Основные компоненты

- **DataProcessor/DataModels** - модели данных с валидацией
- **DataProcessor/GradeCalculator** - логика анализа и округления оценок
- **Utils/FileSystemUtils** - утилиты для работы с файлами
- **AnalysisResult** - хранение результатов анализа

### Бизнес-логика

- **Округление оценок:** дробная часть ≥ 0.6 → округление вверх
- **Критерий одной тройки:** только одна оценка "3" среди всех предметов
- **Критерий нулевого балла:** хотя бы один средний балл равен 0.0

## 🔧 Скрипты верификации

```bash
# Полная проверка Phase 2
./scripts/test_phase2.sh        # Linux
scripts\test_phase2.bat         # Windows

# Проверка релиза 0.1.0
./scripts/verify_release_0.1.0.sh

# Индивидуальные тесты
cd build
./test_datamodels              # Тесты моделей данных
./test_gradecalculator         # Тесты калькулятора (4 сценария)
./test_filesystem              # Тесты файловой системы
./bin/demo_datamodels          # Демонстрационная программа
```

## Генерация документации

### Требования
- Doxygen 1.8.0 или выше
- Graphviz (для диаграмм классов)

### Генерация
```bash
# Сборка документации
mkdir build && cd build
cmake ..
make docs

# Документация будет доступна в build/docs/html/
```

## 🔧 Для разработчиков

### Git Flow

- `feature/*` → CI: RedOS + Windows (ci-feature.yaml)
- `develop` → CI: Продакшен сборка (ci-main.yaml)
- `main` → CI: Стабильная версия (ci-main.yaml)

### Скрипты верификации

```bash
# Полная проверка Phase 2
./scripts/test_phase2.sh        # Linux
scripts\test_phase2.bat         # Windows

# Проверка релиза 0.1.0
./scripts/verify_release_0.1.0.sh

# Индивидуальные тесты
cd build
./test_datamodels              # Тесты моделей данных
./test_gradecalculator         # Тесты калькулятора (4 сценария)
./test_filesystem              # Тесты файловой системы
./bin/demo_datamodels          # Демонстрационная программа
```

### Коммиты

- `WIP:` - черновая работа
- `PROGRES:` - значительный прогресс
- `FEAT:` - завершенная функциональность
- `FIX:` - исправления ошибок
- `TEST:` - тесты и верификация
- `DOCS:` - документация

### Структура Phase 2

```text
AnalyticsApp/
├── src/
│   ├── DataProcessor/     # Модели данных + анализ
│   │   ├── DataModels.h/cpp
│   │   └── GradeCalculator.h/cpp
│   ├── Utils/            # Утилиты файловой системы
│   │   ├── FileSystemUtils.h/cpp
│   │   └── CMakeLists.txt
│   ├── demo_datamodels.cpp  # Демо-программа
│   └── main.cpp
├── tests/
│   ├── test_datamodels.cpp
│   ├── test_gradecalculator.cpp
│   └── test_filesystem.cpp
└── scripts/              # Скрипты верификации
    ├── test_phase2.sh
    ├── test_phase2.bat
    └── verify_release_0.1.0.sh
```

## 📄 Лицензия

MIT License