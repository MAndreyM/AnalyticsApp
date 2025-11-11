#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <algorithm>
#include "DataProcessor/DataModels.h"
#include "DataProcessor/GradeCalculator.h"
#include "FileProcessor/DirectoryScanner.h"
#include "Utils/FileSystemUtils.h"

/**
 * @brief Выводит справку по использованию программы
 */
void printHelp() {
    std::cout << "🚀 AnalyticsApp - Анализ успеваемости учащихся\n";
    std::cout << "Version 0.1.0 - Phase 3 Integration\n";
    std::cout << "===================================\n\n";
    std::cout << "Использование:\n";
    std::cout << "  analytics_app [OPTIONS]\n\n";
    std::cout << "Опции:\n";
    std::cout << "  -h, --help       Показать эту справку\n";
    std::cout << "  -v, --version    Показать версию программы\n";
    std::cout << "  --scan DIR       Просканировать директорию на наличие Excel файлов\n";
    std::cout << "  --demo-data      Запустить демонстрацию анализа данных\n";
    std::cout << "  --demo-fs        Запустить демонстрацию утилит файловой системы\n\n";
    std::cout << "Примеры:\n";
    std::cout << "  analytics_app                    # Запуск в интерактивном режиме\n";
    std::cout << "  analytics_app --help            # Показать справку\n";
    std::cout << "  analytics_app --scan ./data     # Сканировать директорию ./data\n";
    std::cout << "  analytics_app --demo-data       # Демонстрация анализа данных\n";
    std::cout << "  analytics_app --demo-fs         # Демонстрация файловой системы\n\n";
    std::cout << "Функциональность:\n";
    std::cout << "  📊 Анализ данных учащихся с правилами округления оценок\n";
    std::cout << "  🔍 Рекурсивное сканирование директорий для поиска Excel файлов\n";
    std::cout << "  📁 Утилиты для работы с файловой системой\n";
    std::cout << "  🧪 4 комплексных тестовых сценария анализа успеваемости\n";
}

/**
 * @brief Выводит информацию о версии программы
 */
void printVersion() {
    std::cout << "AnalyticsApp Version 0.1.0\n";
    std::cout << "Phase 3: File Processing Integration\n";
    std::cout << "Built with C++20\n";
    std::cout << "Supported platforms: RedOS, Alt Linux, Windows\n";
}

/**
 * @brief Обрабатывает аргументы командной строки
 * 
 * @param argc Количество аргументов
 * @param argv Массив аргументов
 * @return true Если нужно продолжить выполнение в интерактивном режиме
 * @return false Если программа должна завершиться после обработки аргументов
 */
bool handleCommandLineArgs(int argc, char* argv[]) {
    if (argc == 1) {
        // Нет аргументов - запускаем интерактивный режим
        return true;
    }
    
    std::string firstArg = argv[1];
    
    if (firstArg == "-h" || firstArg == "--help") {
        printHelp();
        return false;
    }
    else if (firstArg == "-v" || firstArg == "--version") {
        printVersion();
        return false;
    }
    else if (firstArg == "--scan") {
        if (argc < 3) {
            std::cout << "❌ Ошибка: для опции --scan требуется указать путь к директории\n";
            std::cout << "Использование: analytics_app --scan /path/to/directory\n";
            return false;
        }
        
        std::string directoryPath = argv[2];
        std::cout << "🔍 Сканирование директории: " << directoryPath << "\n";
        
        try {
            DirectoryScanner scanner;
            auto files = scanner.findExcelFiles(directoryPath);
            auto stats = scanner.getLastScanStatistics();
            
            std::cout << "\n🎯 Результаты сканирования:\n";
            if (!files.empty()) {
                std::cout << "✅ Найдено " << files.size() << " Excel файл(ов):\n";
                for (size_t i = 0; i < files.size(); ++i) {
                    std::cout << "   " << (i + 1) << ". " << files[i] << "\n";
                }
            } else {
                std::cout << "❌ Excel файлы не найдены\n";
            }
            
            std::cout << "\n";
            stats.print();
            
        } catch (const std::exception& e) {
            std::cout << "💥 Ошибка: " << e.what() << "\n";
        }
        return false;
    }
    else if (firstArg == "--demo-data") {
        std::cout << "📊 Демонстрация анализа данных\n";
        std::cout << "============================\n";
        
        Student student1("10A", "Иванов Иван Иванович");
        Student student2("10B", "Петрова Анна Сергеевна");
        
        std::cout << "Созданы тестовые студенты:\n";
        std::cout << "  " << student1.getFullName() << " (" << student1.getClassName() << ")\n";
        std::cout << "  " << student2.getFullName() << " (" << student2.getClassName() << ")\n";
        
        std::cout << "\n📈 Возможности калькулятора оценок:\n";
        std::cout << "  - Логика округления оценок (≥ 0.6 → округление вверх)\n";
        std::cout << "  - Анализ успеваемости\n";
        std::cout << "  - 4 комплексных тестовых сценария\n";
        
        std::cout << "\n💡 Для полной демонстрации запустите: ./bin/demo_datamodels\n";
        return false;
    }
    else if (firstArg == "--demo-fs") {
        std::cout << "📁 Демонстрация утилит файловой системы\n";
        std::cout << "============================\n";
        
        std::string testPath = ".";
        std::cout << "📊 Информация о файловой системе:\n";
        std::cout << "  Текущая директория: " << testPath << "\n";
        
        bool exists = std::filesystem::exists(testPath);
        std::cout << "  Существует: " << (exists ? "✅ Да" : "❌ Нет") << "\n";
        
        if (exists) {
            bool is_file = std::filesystem::is_regular_file(testPath);
            bool is_dir = std::filesystem::is_directory(testPath);
            
            std::cout << "  Это файл: " << (is_file ? "📄 Да" : "❌ Нет") << "\n";
            std::cout << "  Это директория: " << (is_dir ? "📁 Да" : "❌ Нет") << "\n";
            
            if (is_dir) {
                size_t fileCount = 0;
                size_t dirCount = 0;
                try {
                    for (const auto& entry : std::filesystem::directory_iterator(testPath)) {
                        if (entry.is_regular_file()) {
                            fileCount++;
                        } else if (entry.is_directory()) {
                            dirCount++;
                        }
                        if (fileCount + dirCount > 5) break;
                    }
                    std::cout << "  Файлов: " << fileCount << ", Директорий: " << dirCount << " (первые 5 элементов)\n";
                } catch (const std::exception& e) {
                    std::cout << "  Содержимое директории: ❌ Не удалось прочитать\n";
                }
            }
        }
        return false;
    }
    else {
        std::cout << "❌ Неизвестная опция: " << firstArg << "\n";
        std::cout << "Используйте --help для просмотра доступных опций\n";
        return false;
    }
}

/**
 * @brief Выводит главное меню приложения
 */
void printMainMenu() {
    std::cout << "\n🎯 AnalyticsApp - Главное меню\n";
    std::cout << "===========================\n";
    std::cout << "1. 📊 Анализ данных студентов\n";
    std::cout << "2. 🔍 Сканирование директории для поиска Excel файлов\n";
    std::cout << "3. 📁 Проверка утилит файловой системы\n";
    std::cout << "4. 🚪 Выход\n";
    std::cout << "===========================\n";
    std::cout << "Выберите опцию (1-4): ";
}

/**
 * @brief Демонстрация анализа данных студентов
 */
void demonstrateDataAnalysis() {
    std::cout << "\n📊 Демонстрация анализа данных студентов\n";
    std::cout << "============================\n";
    
    Student student1("10A", "Иванов Иван Иванович");
    Student student2("10B", "Петрова Анна Сергеевна");
    
    std::cout << "Созданы тестовые студенты:\n";
    std::cout << "  " << student1.getFullName() << " (" << student1.getClassName() << ")\n";
    std::cout << "  " << student2.getFullName() << " (" << student2.getClassName() << ")\n";
    
    std::cout << "\n📈 Возможности калькулятора оценок:\n";
    std::cout << "  - Логика округления оценок (≥ 0.6 → округление вверх)\n";
    std::cout << "  - Анализ успеваемости\n";
    std::cout << "  - 4 комплексных тестовых сценария\n";
    
    std::cout << "\n💡 Для полной демонстрации запустите: ./bin/demo_datamodels\n";
    std::cout << "💡 Для тестирования запустите: ./test_gradecalculator\n";
}

/**
 * @brief Демонстрация сканирования директории
 */
void demonstrateDirectoryScanning() {
    std::cout << "\n🔍 Демонстрация сканирования директории\n";
    std::cout << "=========================\n";
    
    std::string directoryPath;
    std::cout << "Введите путь к директории для сканирования (или нажмите Enter для './test_data'): ";
    std::getline(std::cin, directoryPath);
    
    if (directoryPath.empty()) {
        directoryPath = "./test_data";
    }
    
    try {
        DirectoryScanner scanner;
        
        std::cout << "⏳ Сканирование директории: " << directoryPath << "\n";
        auto files = scanner.findExcelFiles(directoryPath);
        auto stats = scanner.getLastScanStatistics();
        
        std::cout << "\n🎯 Результаты сканирования:\n";
        if (!files.empty()) {
            std::cout << "✅ Найдено " << files.size() << " Excel файл(ов):\n";
            for (size_t i = 0; i < files.size(); ++i) {
                std::cout << "   " << (i + 1) << ". " << files[i] << "\n";
            }
        } else {
            std::cout << "❌ Excel файлы не найдены\n";
        }
        
        std::cout << "\n";
        stats.print();
        
    } catch (const std::exception& e) {
        std::cout << "💥 Ошибка: " << e.what() << "\n";
        std::cout << "💡 Совет: Создайте директорию 'test_data' с несколькими .xls файлами для тестирования\n";
    }
}

/**
 * @brief Демонстрация утилит файловой системы
 */
void demonstrateFileSystemUtilities() {
    std::cout << "\n📁 Демонстрация утилит файловой системы\n";
    std::cout << "============================\n";
    
    std::string testPath;
    std::cout << "Введите путь к файлу/директории для проверки (или нажмите Enter для текущей директории): ";
    std::getline(std::cin, testPath);
    
    if (testPath.empty()) {
        testPath = ".";
    }
    
    try {
        std::cout << "📊 Информация о файловой системе:\n";
        std::cout << "  Путь: " << testPath << "\n";
        
        bool exists = std::filesystem::exists(testPath);
        std::cout << "  Существует: " << (exists ? "✅ Да" : "❌ Нет") << "\n";
        
        if (exists) {
            bool is_file = std::filesystem::is_regular_file(testPath);
            bool is_dir = std::filesystem::is_directory(testPath);
            
            std::cout << "  Это файл: " << (is_file ? "📄 Да" : "❌ Нет") << "\n";
            std::cout << "  Это директория: " << (is_dir ? "📁 Да" : "❌ Нет") << "\n";
            
            if (is_file) {
                std::filesystem::path path(testPath);
                std::string extension = path.extension().string();
                std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
                
                std::cout << "  Это Excel файл: " << (extension == ".xls" ? "📊 Да" : "❌ Нет") << "\n";
                
                try {
                    auto size = std::filesystem::file_size(testPath);
                    std::cout << "  Размер файла: " << size << " байт\n";
                } catch (const std::exception& e) {
                    std::cout << "  Размер файла: ❌ Не удалось определить\n";
                }
            }
            
            if (is_dir) {
                size_t fileCount = 0;
                size_t dirCount = 0;
                try {
                    for (const auto& entry : std::filesystem::directory_iterator(testPath)) {
                        if (entry.is_regular_file()) {
                            fileCount++;
                        } else if (entry.is_directory()) {
                            dirCount++;
                        }
                        if (fileCount + dirCount > 10) break;
                    }
                    std::cout << "  Файлов: " << fileCount << ", Директорий: " << dirCount << " (первые 10 элементов)\n";
                } catch (const std::exception& e) {
                    std::cout << "  Содержимое директории: ❌ Не удалось прочитать\n";
                }
            }
        }
        
    } catch (const std::exception& e) {
        std::cout << "💥 Ошибка: " << e.what() << "\n";
    }
}

/**
 * @brief Основная функция приложения
 */
int main(int argc, char* argv[]) {
    // Обрабатываем аргументы командной строки
    if (!handleCommandLineArgs(argc, argv)) {
        return 0;
    }
    
    // Если аргументов нет или они обработаны, запускаем интерактивный режим
    std::cout << "🚀 Welcome to AnalyticsApp!\n";
    std::cout << "Version 0.1.0 - Phase 3 Integration\n";
    std::cout << "===================================\n";
    
    bool running = true;
    
    while (running) {
        printMainMenu();
        
        std::string input;
        std::getline(std::cin, input);
        
        if (input.empty()) {
            continue;
        }
        
        int choice = 0;
        try {
            choice = std::stoi(input);
        } catch (const std::exception& e) {
            std::cout << "❌ Неверный ввод. Пожалуйста, введите число 1-4.\n";
            continue;
        }
        
        switch (choice) {
            case 1:
                demonstrateDataAnalysis();
                break;
                
            case 2:
                demonstrateDirectoryScanning();
                break;
                
            case 3:
                demonstrateFileSystemUtilities();
                break;
                
            case 4:
                running = false;
                std::cout << "\n👋 Thank you for using AnalyticsApp! Goodbye!\n";
                break;
                
            default:
                std::cout << "❌ Неверная опция. Пожалуйста, выберите 1-4.\n";
                break;
        }
        
        if (running && choice != 4) {
            std::cout << "\nНажмите Enter для продолжения...";
            std::cin.get();
        }
    }
    
    return 0;
}