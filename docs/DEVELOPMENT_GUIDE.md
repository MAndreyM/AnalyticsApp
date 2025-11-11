# Руководство разработчика AnalyticsApp

## 🏗️ Архитектура проекта

### Структура модулей
```
AnalyticsApp/
├── src/
│   ├── DataProcessor/     # Модели данных + анализ
│   ├── Utils/            # Базовые утилиты
│   └── FileProcessor/    # Обработка файлов (Phase 3)
├── tests/                # Unit тесты
├── scripts/              # Скрипты сборки и тестирования
└── docs/                 # Документация
```

### Зависимости между модулями
```
FileProcessor → Utils → DataProcessor
    ↓              ↓          ↓
Main Application → Все модули
```

## 🔧 Сборка и разработка

### Требования
- CMake ≥ 3.16
- Ninja (рекомендуется) или Make
- C++20 компилятор (GCC, Clang, MSVC)
- doctest (загружается автоматически)

### Быстрый старт
```bash
# Клонирование и сборка
git clone <repository>
cd AnalyticsApp
mkdir build && cd build
cmake -G Ninja ..
ninja

# Запуск тестов
ninja test
# или
ctest --output-on-failure

# Запуск приложения
./bin/analytics_app
```

### Скрипты разработки
```bash
# Полная проверка Phase 3
./scripts/test_phase3.sh

# Интеграционное тестирование
./scripts/test_integration.sh

# Все тесты
./scripts/run_all_tests.sh
```

## 📝 Стандарты кодирования

### Стиль кода
- **Именование**: camelCase для методов, PascalCase для классов
- **Отступы**: 4 пробела
- **Комментарии**: Doxygen стиль для публичного API
- **Язык**: Комментарии на русском, код на английском

### Пример класса
```cpp
/**
 * @brief Сканер директорий для поиска Excel файлов
 */
class DirectoryScanner {
public:
    /**
     * @brief Находит все Excel файлы в указанной директории
     */
    std::vector<std::string> findExcelFiles(const std::string& directoryPath);
    
private:
    void validateInputParameters(const std::string& directoryPath) const;
};
```

### Обработка ошибок
- Использовать исключения для ошибок времени выполнения
- `DataValidationException` для ошибок валидации данных
- `std::runtime_error` для системных ошибок

## 🧪 Тестирование

### Структура тестов
```cpp
TEST_CASE("DirectoryScanner basic functionality") {
    SUBCASE("scan non-existent directory throws exception") {
        CHECK_THROWS_AS(scanner.findExcelFiles("/invalid"), std::runtime_error);
    }
    
    SUBCASE("finds all excel files recursively") {
        auto files = scanner.findExcelFiles(testDir);
        CHECK(files.size() == expectedCount);
    }
}
```

### Запуск тестов
```bash
# Все тесты
cd build && ctest --output-on-failure

# Конкретный тест
./test_directory_scanner
./test_gradecalculator
```

## 📚 Документация

### Генерация документации
```bash
cd build
cmake .. -DBUILD_DOCS=ON
ninja docs
# Документация будет в build/docs/html/
```

### Комментарии Doxygen
```cpp
/**
 * @brief Основная функция приложения
 * 
 * @param argc Количество аргументов командной строки
 * @param argv Массив аргументов командной строки
 * @return int Код возврата: 0 - успех, 1 - ошибка
 * 
 * @note При запуске без аргументов запускается интерактивный режим
 * @see printHelp() для списка доступных опций
 */
int main(int argc, char* argv[]) {
    // ...
}
```

## 🔄 Git Workflow

### Ветвление
- `main` - стабильная версия
- `develop` - разработка
- `feature/*` - новые функции
- `hotfix/*` - срочные исправления

### Коммиты
- `feat:` Новая функциональность
- `fix:` Исправление ошибок
- `docs:` Изменения в документации
- `test:` Добавление или исправление тестов
- `refactor:` Рефакторинг кода
- `build:` Изменения в системе сборки

### Пример коммита
```
feat: add DirectoryScanner with recursive file search

- Implement recursive directory scanning for .xls files
- Add scan statistics with timing and error tracking
- Integrate with main application menu system
- Add comprehensive unit tests

Closes #123
```

## 🐳 Docker разработка

### Локальное тестирование на RedOS
```bash
docker run --rm -v $(pwd):/workspace mandrm/redos-ci-analytics:latest \
  bash -c "cd /workspace && mkdir build && cd build && cmake -G Ninja .. && ninja"
```

### Локальное тестирование на Alt Linux
```bash
docker run --rm -v $(pwd):/workspace mandrm/altlinux-ci-analytics:latest \
  bash -c "cd /workspace && mkdir build && cd build && cmake -G Ninja .. && ninja"
```

## 🔍 Отладка

### Common Issues
1. **Ошибки линковки**: Проверить зависимости в CMakeLists.txt
2. **Файлы не найдены**: Проверить рабочий директорий и пути
3. **Исключения filesystem**: Проверить права доступа к файлам

### Логирование
```cpp
#include <iostream>

// Для отладки
std::cout << "🔍 Scanning directory: " << path << std::endl;

// Для ошибок
std::cerr << "💥 Error: " << e.what() << std::endl;
```

## 🚀 Deployment

### Требования к production
- C++20 runtime
- Поддержка filesystem
- Доступ к файловой системе для чтения

### Проверка сборки
```bash
./scripts/verify_build.sh
./scripts/test_phase3.sh
```

---

*Это руководство будет обновляться по мере развития проекта.*