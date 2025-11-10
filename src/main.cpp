/**
 * @file main.cpp
 * @brief Главный файл приложения для анализа успеваемости учащихся
 * @author MAndreyM
 * @version 1.0.0
 * @date 2024
 */

#include "DataProcessor/DataModels.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

/**
 * @brief Структура для хранения параметров командной строки
 * 
 * Содержит все опции, переданные при запуске приложения.
 */
struct CommandLineOptions {
    std::string inputDirectory;    ///< Путь к директории с входными файлами
    std::string outputDirectory = ".";  ///< Путь для выходных отчетов (по умолчанию: текущая директория)
    bool verbose = false;          ///< Флаг подробного вывода
    bool helpRequested = false;    ///< Флаг запроса справки
};

/**
 * @brief Класс для разбора аргументов командной строки
 * 
 * Обрабатывает аргументы, переданные при запуске приложения,
 * и преобразует их в структуру CommandLineOptions.
 */
class CommandLineParser {
public:
    /**
     * @brief Разбирает аргументы командной строки
     * 
     * @param argc Количество аргументов
     * @param argv Массив аргументов
     * @return CommandLineOptions Структура с разобранными параметрами
     * @throw std::runtime_error Если обязательные параметры не указаны
     * 
     * @note Поддерживаемые опции:
     * - -h, --help: Показать справку
     * - -v, --verbose: Включить подробный вывод
     * - -o, --output: Указать директорию для отчетов
     */
    CommandLineOptions parse(int argc, char* argv[]) {
        CommandLineOptions options;
        
        if (argc < 2) {
            options.helpRequested = true;
            return options;
        }
        
        std::vector<std::string> args(argv + 1, argv + argc);
        
        for (size_t i = 0; i < args.size(); ++i) {
            if (args[i] == "-h" || args[i] == "--help") {
                options.helpRequested = true;
                return options;
            } else if (args[i] == "-v" || args[i] == "--verbose") {
                options.verbose = true;
            } else if (args[i] == "-o" || args[i] == "--output") {
                if (i + 1 < args.size()) {
                    options.outputDirectory = args[++i];
                } else {
                    throw std::runtime_error("Output directory not specified");
                }
            } else {
                // Первый неопциональный аргумент - входная директория
                if (options.inputDirectory.empty()) {
                    options.inputDirectory = args[i];
                }
            }
        }
        
        if (options.inputDirectory.empty() && !options.helpRequested) {
            throw std::runtime_error("Input directory not specified");
        }
        
        return options;
    }
    
    /**
     * @brief Выводит справку по использованию программы
     * 
     * @param programName Имя программы (argv[0])
     */
    void printHelp(const std::string& programName) {
        std::cout << "Usage: " << programName << " [OPTIONS] INPUT_DIRECTORY\n\n"
                  << "Analyze student performance data from Excel files\n\n"
                  << "Arguments:\n"
                  << "  INPUT_DIRECTORY    Path to directory containing .xls files\n\n"
                  << "Options:\n"
                  << "  -o, --output DIR   Output directory for reports (default: current dir)\n"
                  << "  -v, --verbose      Enable verbose output\n"
                  << "  -h, --help         Show this help message\n\n"
                  << "Examples:\n"
                  << "  " << programName << " /path/to/data\n"
                  << "  " << programName << " -o ./reports /path/to/data\n"
                  << "  " << programName << " -v --output ./results /path/to/data\n";
    }
};

/**
 * @brief Класс для логирования сообщений приложения
 * 
 * Поддерживает разные уровни логирования: info, warning, error, debug.
 * Debug сообщения выводятся только в verbose режиме.
 */
class Logger {
private:
    bool verbose_;  ///< Флаг включения подробного вывода
    
public:
    /**
     * @brief Конструктор логгера
     * 
     * @param verbose Включить подробный вывод (по умолчанию: false)
     */
    explicit Logger(bool verbose = false) : verbose_(verbose) {}
    
    /**
     * @brief Устанавливает режим подробного вывода
     * 
     * @param verbose Если true, debug сообщения будут выводиться
     */
    void setVerbose(bool verbose) {
        verbose_ = verbose;
    }
    
    /**
     * @brief Выводит информационное сообщение
     * 
     * @param message Текст сообщения
     */
    void info(const std::string& message) {
        std::cout << "[INFO] " << message << std::endl;
    }
    
    /**
     * @brief Выводит предупреждение
     * 
     * @param message Текст предупреждения
     */
    void warning(const std::string& message) {
        std::cout << "[WARNING] " << message << std::endl;
    }
    
    /**
     * @brief Выводит сообщение об ошибке
     * 
     * @param message Текст ошибки
     */
    void error(const std::string& message) {
        std::cerr << "[ERROR] " << message << std::endl;
    }
    
    /**
     * @brief Выводит отладочное сообщение (только в verbose режиме)
     * 
     * @param message Текст отладочного сообщения
     */
    void debug(const std::string& message) {
        if (verbose_) {
            std::cout << "[DEBUG] " << message << std::endl;
        }
    }
};

/**
 * @brief Основная функция приложения
 * 
 * @param argc Количество аргументов командной строки
 * @param argv Массив аргументов командной строки
 * @return int Код возврата: 0 - успех, 1 - ошибка
 * 
 * @par Пример использования:
 * @code{.sh}
 * ./analytics_app /path/to/data
 * ./analytics_app -v -o ./reports /path/to/data
 * ./analytics_app --help
 * @endcode
 */
int main(int argc, char* argv[]) {
    CommandLineParser parser;
    Logger logger;
    
    try {
        CommandLineOptions options = parser.parse(argc, argv);
        
        if (options.helpRequested) {
            parser.printHelp(argv[0]);
            return 0;
        }
        
        logger.setVerbose(options.verbose);
        logger.info("Analytics App - Starting...");
        logger.debug("Verbose mode enabled");
        
        // Вывод информации о параметрах
        logger.info("Input directory: " + options.inputDirectory);
        logger.info("Output directory: " + options.outputDirectory);
        
        // Здесь будет основная логика приложения
        logger.info("Processing directory: " + options.inputDirectory);
        
        // Заглушка для демонстрации
        logger.debug("Scanning for Excel files...");
        logger.debug("Parsing student data...");
        logger.debug("Analyzing performance...");
        logger.debug("Generating reports...");
        
        logger.info("Processing completed successfully!");
        
    } catch (const std::exception& e) {
        logger.error(e.what());
        std::cerr << "\nUse '" << argv[0] << " --help' for usage information.\n";
        return 1;
    } catch (...) {
        logger.error("Unknown error occurred");
        return 1;
    }
    
    return 0;
}