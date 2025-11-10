# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.1.0] - 2024-XX-XX

### Added
- Базовая структура проекта с CMake и Ninja
- Модели данных Student и AnalysisResult с валидацией
- GradeCalculator с логикой округления оценок
- 4 комплексных тестовых сценария анализа успеваемости
- Демонстрационная программа с выводом в требуемом формате
- Утилиты для работы с файловой системой (FileSystemUtils)
- Полная система тестирования с doctest
- Валидация данных и обработка ошибок
- Документация Doxygen
- Кроссплатформенная сборка (RedOS, Alt Linux, Windows)
- CI/CD пайплайны для feature веток и production
- Скрипты верификации для Phase 2

### Testing
- Unit-тесты для всех основных компонентов
- Интеграционные тесты для 4 сценариев анализа
- Автоматическая проверка формата вывода
- Кроссплатформенное тестирование на CI/CD

### Technical
- Модульная структура проекта (DataProcessor, Utils)
- Поддержка C++20 стандарта
- Настройка системы сборки с установкой
- Конфигурация CPack для пакетирования
- Поддержка std::filesystem

### Documentation
- Полная документация API с Doxygen
- README с инструкциями по сборке и использованию
- Описание архитектуры и бизнес-логики
- Примеры кода и тестовые сценарии