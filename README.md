# Analytics App - Анализ успеваемости учащихся

## 📊 CI/CD Status

| Ветка | Статус | Описание |
|-------|--------|-----------|
| `develop` | ![Develop CI](https://github.com/MAndreyM/AnalyticsApp/actions/workflows/ci-develop.yml/badge.svg?branch=develop) | Интеграционная сборка |
| `main` | ![Main CI](https://github.com/MAndreyM/AnalyticsApp/actions/workflows/ci-main.yml/badge.svg?branch=main) | Production сборка |
| `feature/*` | ![Feature CI](https://github.com/MAndreyM/AnalyticsApp/actions/workflows/ci-feature.yml/badge.svg) | Функциональные ветки |

## 🔄 Workflow Status

| Workflow | Статус |
|----------|--------|
| Release | ![Release](https://github.com/MAndreyM/AnalyticsApp/actions/workflows/release.yml/badge.svg) |

## 🚀 О проекте

Кроссплатформенное приложение для анализа успеваемости учащихся на основе данных из Excel файлов.

## 📋 Функциональность

- ✅ Чтение XLS файлов
- ✅ Анализ успеваемости 
- ✅ Генерация отчетов
- ✅ Кроссплатформенность

## Поддерживаемые платформы
- ✅ RedOS
- ✅ Alt Linux (10, latest)  
- ✅ Windows (MinGW-w64)

## 🛠 Сборка и запуск

### Требования
- CMake ≥ 3.16
- Ninja
- C++20 компилятор (GCC, Clang, MSVC)

### Linux/RedOS
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

## 🔧 Для разработчиков

### Git Flow

- main - стабильные версии
- develop - текущая разработка
- feature/* - новые функции
- hotfix/* - срочные исправления

### Коммиты

- `WIP:` - черновая работа
- `PROGRES:` - значительный прогресс
- `FEAT:` - завершенная функциональность
- `FIX:` - исправления ошибок
- `DOCS:` - документация

## 📄 Лицензия

MIT License