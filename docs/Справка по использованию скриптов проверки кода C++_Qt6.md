# Справка по использованию скриптов проверки кода C++/Qt6

## Общая информация

Набор скриптов предназначен для автоматической проверки форматирования и статического анализа кода C++ с использованием `clang-format` и `clang-tidy`. Скрипты настроены для работы с проектами C++20/Qt6 и используют конфигурационные файлы `.clang-format` и `.clang-tidy`.

**Операционная система:** RedOS (и другие дистрибутивы на основе RHEL/Fedora)

## Предварительные требования

### 1. Установка необходимых пакетов

```bash
# Войдите в систему как root или используйте sudo
sudo su

# Обновите систему
dnf update -y

# Установите LLVM, Clang и дополнительные инструменты
dnf install -y llvm clang clang-tools-extra

# Для проектов Qt6 установите необходимые пакеты
dnf install -y qt6-devel cmake make

# Проверьте версию установленных инструментов
clang-format --version
clang-tidy --version
```

### 2. Настройка проекта

Убедитесь, что в корне вашего проекта находятся следующие файлы:
- `.clang-format` - конфигурация форматирования
- `.clang-tidy` - конфигурация статического анализа
- Каталог `scripts/` со всеми скриптами
- Исходный код в каталоге `src/`

### 3. Настройка прав доступа

```bash
# Перейдите в корень проекта
cd /путь/к/вашему/проекту

# Сделайте скрипты исполняемыми
chmod +x scripts/*.sh

# Проверьте права доступа
ls -la scripts/
```

## Список скриптов

| Скрипт | Назначение | Время выполнения |
|--------|------------|------------------|
| `check-format.sh` | Проверка форматирования кода | 1-30 сек |
| `fix-format.sh` | Автоматическое исправление форматирования | 1-60 сек |
| `check-tidy.sh` | Статический анализ кода | 10-300 сек |
| `check-all.sh` | Запуск всех проверок | 15-360 сек |

## Подробное описание скриптов

### 1. `scripts/check-format.sh`

**Назначение:** Проверяет соответствие кода стандартам форматирования, заданным в `.clang-format`.

**Использование:**
```bash
./scripts/check-format.sh
```

**Вывод:**
```
=== Проверка форматирования кода ===
Проверка: src/main.cpp
  ✅ Форматирование корректно
Проверка: src/utils/helper.cpp
  ❌ Требуется форматирование
  Для исправления запустите: clang-format -style=file -i src/utils/helper.cpp

=== Результаты проверки ===
Проверено файлов: 15
Файлов с ошибками форматирования: 2
```

**Коды возврата:**
- `0` - все файлы корректно отформатированы
- `1` - обнаружены ошибки форматирования

### 2. `scripts/fix-format.sh`

**Назначение:** Автоматически исправляет форматирование кода.

**Использование:**
```bash
./scripts/fix-format.sh
```

**Важно:** Скрипт создает резервные копии файлов с расширением `.backup` перед изменением.

**Вывод:**
```
=== Исправление форматирования кода ===
Обработка: src/main.cpp
  ⏭️  Без изменений
Обработка: src/utils/helper.cpp
  ✅ Исправлено

=== Результаты ===
Обработано файлов: 15
Исправлено файлов: 3
```

### 3. `scripts/check-tidy.sh`

**Назначение:** Выполняет статический анализ кода с помощью `clang-tidy`.

**Использование:**
```bash
./scripts/check-tidy.sh
```

**Особенности:**
- Автоматически исключает `moc_` файлы Qt
- Создает подробные отчеты в каталоге `reports/tidy/`
- Настраивается через `.clang-tidy`
- Поддерживает C++20 и пути включения Qt6

**Вывод:**
```
=== Статический анализ кода ===
Анализ: src/main.cpp
  ✅ Без ошибок и предупреждений
Анализ: src/utils/helper.cpp
  ⚠️  Найдено: 0 ошибок, 5 предупреждений

=== Результаты анализа ===
Проверено файлов: 15
Найдено ошибок: 0
Найдено предупреждений: 12
```

**Каталог отчетов:** `reports/tidy/`

### 4. `scripts/check-all.sh`

**Назначение:** Запускает все проверки последовательно.

**Использование:**
```bash
./scripts/check-all.sh
```

**Последовательность выполнения:**
1. Проверка наличия утилит
2. Проверка форматирования (`check-format.sh`)
3. Статический анализ (`check-tidy.sh`)

## Интеграция с системой сборки

### Для CMake проектов:

Добавьте в `CMakeLists.txt`:

```cmake
# Цель для проверки форматирования
add_custom_target(check-format
    COMMAND ${CMAKE_SOURCE_DIR}/scripts/check-format.sh
    COMMENT "Проверка форматирования кода"
)

# Цель для исправления форматирования
add_custom_target(fix-format
    COMMAND ${CMAKE_SOURCE_DIR}/scripts/fix-format.sh
    COMMENT "Исправление форматирования кода"
)

# Цель для статического анализа
add_custom_target(check-tidy
    COMMAND ${CMAKE_SOURCE_DIR}/scripts/check-tidy.sh
    COMMENT "Статический анализ кода"
)

# Цель для всех проверок
add_custom_target(check-all
    COMMAND ${CMAKE_SOURCE_DIR}/scripts/check-all.sh
    COMMENT "Запуск всех проверок кода"
)
```

Использование:
```bash
cmake -B build
cmake --build build --target check-all
```

### Для Make проектов:

Добавьте в `Makefile`:

```makefile
.PHONY: check-format fix-format check-tidy check-all

check-format:
	./scripts/check-format.sh

fix-format:
	./scripts/fix-format.sh

check-tidy:
	./scripts/check-tidy.sh

check-all:
	./scripts/check-all.sh
```

## Интеграция с CI/CD (GitLab CI)

Пример `.gitlab-ci.yml`:

```yaml
stages:
  - checks

format-check:
  stage: checks
  image: registry.redos.red-soft.ru/base/redos:7.3
  script:
    - dnf install -y llvm clang clang-tools-extra
    - ./scripts/check-format.sh
  only:
    - merge_requests
    - main

tidy-check:
  stage: checks
  image: registry.redos.red-soft.ru/base/redos:7.3
  script:
    - dnf install -y llvm clang clang-tools-extra qt6-devel
    - ./scripts/check-tidy.sh
  only:
    - merge_requests
    - main
  artifacts:
    paths:
      - reports/tidy/
    when: always
    expire_in: 1 week
```

## Решение распространенных проблем

### 1. Ошибка "clang-format не найден"
```bash
sudo dnf install -y clang-tools-extra
```

### 2. Ошибка "Нет доступа к скриптам"
```bash
chmod +x scripts/*.sh
```

### 3. Ошибки при анализе Qt кода
Убедитесь, что установлены заголовки Qt6:
```bash
sudo dnf install -y qt6-devel
```

### 4. Медленная работа clang-tidy
Для больших проектов можно использовать параллельный запуск:

Создайте `scripts/check-tidy-parallel.sh`:
```bash
#!/bin/bash
find src -name "*.cpp" | xargs -P 4 -I {} clang-tidy --config-file=.clang-tidy.txt {}
```

### 5. Пропуск определенных файлов
Отредактируйте скрипты, добавив исключения:
```bash
# В check-format.sh и check-tidy.sh добавьте:
FILES=$(find src -name "*.cpp" -o -name "*.hpp" | grep -v "third_party/" | grep -v "generated/")
```

## Полезные команды для отладки

### Проверка конфигурации clang-format:
```bash
# Показать текущую конфигурацию
clang-format -style=file -dump-config

# Проверить форматирование одного файла
clang-format -style=file src/main.cpp

# Показать различия
clang-format -style=file src/main.cpp | diff -u src/main.cpp -
```

### Проверка конфигурации clang-tidy:
```bash
# Список доступных проверок
clang-tidy --list-checks

# Проверка одного файла с выводом
clang-tidy --config-file=.clang-tidy.txt src/main.cpp --
```

### Поиск всех C++ файлов в проекте:
```bash
find src -type f \( -name "*.cpp" -o -name "*.hpp" -o -name "*.cc" -o -name "*.hh" \) | wc -l
```

## Автоматизация (хуки Git)

### Предкоммитный хук:
Создайте `.git/hooks/pre-commit`:
```bash
#!/bin/bash
echo "Запуск проверки форматирования..."
if ! ./scripts/check-format.sh; then
    echo "Ошибка форматирования! Исправьте с помощью: ./scripts/fix-format.sh"
    exit 1
fi
echo "✅ Форматирование проверено"
```

Сделайте исполняемым:
```bash
chmod +x .git/hooks/pre-commit
```

## Оптимизация производительности

1. **Кэширование компиляции:**
```bash
export CMAKE_EXPORT_COMPILE_COMMANDS=ON
```

2. **Использование файла компиляции:**
Добавьте в скрипты `check-tidy.sh`:
```bash
if [[ -f "compile_commands.json" ]]; then
    clang-tidy --config-file=.clang-tidy.txt -p .
else
    # текущая реализация
fi
```

3. **Параллельная обработка:**
Установите `parallel`:
```bash
sudo dnf install -y parallel
```

## Контакты и поддержка

- **Документация Clang:** https://clang.llvm.org/extra/clang-tidy/
- **Документация RedOS:** https://www.redos.red-soft.ru/support/docs/
- **Форум RedOS:** https://forum.redos.red-soft.ru/

## Лицензия

Скрипты распространяются под лицензией MIT. Используйте свободно в своих проектах.

---
*Последнее обновление: $(date)*
*Адаптировано для RedOS 7.3+*