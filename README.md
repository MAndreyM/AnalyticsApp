# Analytics App - Анализ успеваемости учащихся

Кроссплатформенное приложение для анализа успеваемости учащихся на основе данных из Excel файлов.

## Поддерживаемые платформы
- ✅ RedOS
- ✅ Alt Linux (10, latest)  
- ✅ Windows (MinGW-w64)

## Сборка

### Linux
```bash
mkdir build && cd build
cmake -G Ninja ..
ninja
```

### Windows

```cmd
build.bat
```

### Использование

```bash
./analytics_app [OPTIONS] INPUT_DIRECTORY

Options:
  -o, --output DIR   Output directory for reports
  -v, --verbose      Enable verbose output  
  -h, --help         Show this help message
```

### Разработка

```bash
# Проверка готовности к CI
./scripts/ci_setup.sh

# Быстрая сборка (Windows)
build.bat

# Очистка
clean.bat
```

### Лицензия
Проект распространяется под лицензией MIT.