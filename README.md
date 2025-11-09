# Analytics App - Анализ успеваемости учащихся

## 📊 CI/CD Status

| Ветка | Статус | Платформы |
|-------|--------|-----------|
| Feature Branches | ![Feature CI](https://github.com/MAndreyM/AnalyticsApp/actions/workflows/ci-feature.yaml/badge.svg) | RedOS, Alt Linux, Windows |
| Develop Branch | ![Develop CI](https://github.com/MAndreyM/AnalyticsApp/actions/workflows/ci-main.yaml/badge.svg?branch=develop) | Продакшен сборка |
| Main Branch | ![Main CI](https://github.com/MAndreyM/AnalyticsApp/actions/workflows/ci-main.yaml/badge.svg?branch=main) | Стабильная версия |

## 🚀 О проекте
Кроссплатформенное CLI приложение для анализа успеваемости учащихся на основе данных из Excel файлов.

## 📋 Поддерживаемые платформы

- ✅ **RedOS** - основная целевая платформа
- ✅ **Alt Linux Latest** - актуальная версия
- ✅ **Alt Linux 10** - стабильная версия  
- ✅ **Windows** - поддержка MSVC

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

### Коммиты

- `WIP:` - черновая работа
- `PROGRES:` - значительный прогресс
- `FEAT:` - завершенная функциональность
- `FIX:` - исправления ошибок
- `DOCS:` - документация

## 📄 Лицензия

MIT License