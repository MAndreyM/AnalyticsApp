# Analytics App - Анализ успеваемости учащихся

## 📊 CI/CD Status

| Ветка | Статус | Платформы |
|-------|--------|-----------|
| Feature Branches | ![Feature CI](https://github.com/MAndreyM/AnalyticsApp/actions/workflows/ci-feature.yaml/badge.svg) | RedOS & Windows |
| Develop Branch | ![Develop CI](https://github.com/MAndreyM/AnalyticsApp/actions/workflows/ci-main.yaml/badge.svg?branch=develop) | Продакшен сборка |
| Main Branch | ![Main CI](https://github.com/MAndreyM/AnalyticsApp/actions/workflows/ci-main.yaml/badge.svg?branch=main) | Стабильная версия |

## 🚀 О проекте
Кроссплатформенное CLI приложение для анализа успеваемости учащихся на основе данных из Excel файлов.

## 📋 Поддерживаемые платформы

- ✅ **RedOS** - основная целевая платформа
- ✅ **Windows** - поддержка MSVC
- 🔄 **Alt Linux** - в разработке

## 🐳 Используемые Docker образы

Для CI/CD используются предварительно собранные Docker образы:

```bash
# RedOS CI образ
docker pull mandreym/redos-ci-analytics:latest

# Локальное тестирование
docker run --rm -v $(pwd):/workspace mandreym/redos-ci-analytics:latest \
  bash -c "mkdir build && cd build && cmake -G Ninja .. && ninja"
```

## 🛠 Сборка и запуск

### Требования
- CMake ≥ 3.16
- Ninja
- C++20 компилятор (GCC, Clang, MSVC)

### RedOS

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

- `feature/*` → CI: RedOS + Windows (ci-feature.yaml)
- `develop` → CI: Продакшен сборка (ci-main.yaml)
- `main` → CI: Стабильная версия (ci-main.yaml)

### Коммиты

- `WIP:` - черновая работа
- `PROGRES:` - значительный прогресс
- `FEAT:` - завершенная функциональность
- `FIX:` - исправления ошибок
- `DOCS:` - документация

## 📄 Лицензия

MIT License