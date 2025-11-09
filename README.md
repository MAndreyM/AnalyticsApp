# Analytics App - Анализ успеваемости учащихся

## 📊 CI/CD Status

| Платформа | Статус | Детали |
|-----------|--------|---------|
| Все платформы | ![CI Status](https://github.com/MAndreyM/AnalyticsApp/actions/workflows/ci-simple.yaml/badge.svg) | Ubuntu & Windows |
| Develop ветка | ![Develop CI](https://github.com/MAndreyM/AnalyticsApp/actions/workflows/ci-simple.yaml/badge.svg?branch=develop) | Основная разработка |
| Main ветка | ![Main CI](https://github.com/MAndreyM/AnalyticsApp/actions/workflows/ci-simple.yaml/badge.svg?branch=main) | Продакшен сборка |

## 🚀 О проекте
Кроссплатформенное CLI приложение для анализа успеваемости учащихся на основе данных из Excel файлов.

## 📋 Поддерживаемые платформы

- ✅ **Ubuntu** - основная сборка
- ✅ **Windows** - поддержка MSVC/MinGW
- ✅ **RedOS** - в разработке
- ✅ **Alt Linux** - в разработке


## 🛠 Сборка и запуск

### Требования
- CMake ≥ 3.16
- Ninja
- C++20 компилятор (GCC, Clang, MSVC)

### Linux/Ubuntu
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