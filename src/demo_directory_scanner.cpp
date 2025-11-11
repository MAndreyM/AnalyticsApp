#include <iostream>
#include <iomanip>
#include <string>
#include "FileProcessor/DirectoryScanner.h"

/**
 * @brief Выводит справку по использованию программы
 * 
 * @param programName Имя программы (argv[0])
 */
void printUsage(const std::string& programName) {
    std::cout << "🔍 Directory Scanner Demo\n";
    std::cout << "=========================\n\n";
    std::cout << "Usage: " << programName << " [OPTIONS] DIRECTORY_PATH\n\n";
    std::cout << "Recursively scans directory for Excel files (.xls)\n\n";
    std::cout << "Arguments:\n";
    std::cout << "  DIRECTORY_PATH    Path to directory to scan\n\n";
    std::cout << "Options:\n";
    std::cout << "  -h, --help       Show this help message\n";
    std::cout << "  -v, --verbose    Show detailed scanning information\n\n";
    std::cout << "Examples:\n";
    std::cout << "  " << programName << " /path/to/data\n";
    std::cout << "  " << programName << " C:\\Users\\Data\n";
    std::cout << "  " << programName << " test_data\n";
    std::cout << "  " << programName << " --help\n";
}

/**
 * @brief Выводит результаты сканирования в форматированном виде
 * 
 * @param files Найденные Excel файлы
 * @param stats Статистика сканирования
 * @param verbose Флаг подробного вывода
 */
void printResults(const std::vector<std::string>& files, 
                  const DirectoryScanner::ScanStatistics& stats,
                  bool verbose = false) {
    
    std::cout << "\n🎯 Scan Results\n";
    std::cout << "================\n";
    
    if (!files.empty()) {
        std::cout << "✅ Found " << files.size() << " Excel file(s):\n";
        for (size_t i = 0; i < files.size(); ++i) {
            std::cout << "   " << std::setw(2) << (i + 1) << ". " << files[i] << std::endl;
        }
    } else {
        std::cout << "❌ No Excel files found with .xls extension\n";
    }
    
    std::cout << "\n";
    stats.print();
    
    if (verbose) {
        std::cout << "\n📈 Detailed Statistics:\n";
        std::cout << "   📊 Success rate: " 
                  << (stats.totalFilesScanned > 0 ? 
                      (stats.excelFilesFound * 100 / stats.totalFilesScanned) : 0) 
                  << "% of files are Excel files\n";
        std::cout << "   📁 Directory scan ratio: " 
                  << (stats.excelFilesFound > 0 ? 
                      (stats.directoriesScanned / stats.excelFilesFound) : 0) 
                  << " directories per Excel file\n";
    }
}

/**
 * @brief Обрабатывает аргументы командной строки
 * 
 * @param argc Количество аргументов
 * @param argv Массив аргументов
 * @param directoryPath Возвращает путь к директории
 * @param verbose Возвращает флаг подробного вывода
 * @param helpRequested Возвращает флаг запроса справки
 * @return true Если аргументы корректны
 * @return false Если аргументы неверны
 */
bool parseArguments(int argc, char* argv[], 
                   std::string& directoryPath, 
                   bool& verbose, 
                   bool& helpRequested) {
    
    if (argc < 2) {
        return false;
    }
    
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        
        if (arg == "-h" || arg == "--help") {
            helpRequested = true;
            return true;
        } else if (arg == "-v" || arg == "--verbose") {
            verbose = true;
        } else if (arg.empty()) {
            continue;
        } else if (arg[0] == '-') {
            std::cerr << "❌ Unknown option: " << arg << std::endl;
            return false;
        } else {
            // Первый не-опциональный аргумент - путь к директории
            if (directoryPath.empty()) {
                directoryPath = arg;
            } else {
                std::cerr << "❌ Multiple directory paths specified: " 
                          << directoryPath << " and " << arg << std::endl;
                return false;
            }
        }
    }
    
    return !directoryPath.empty() || helpRequested;
}

/**
 * @brief Основная функция демо-программы
 * 
 * @param argc Количество аргументов командной строки
 * @param argv Массив аргументов командной строки
 * @return int Код возврата: 0 - успех, 1 - ошибка
 */
int main(int argc, char* argv[]) {
    std::string directoryPath;
    bool verbose = false;
    bool helpRequested = false;
    
    // Парсим аргументы командной строки
    if (!parseArguments(argc, argv, directoryPath, verbose, helpRequested)) {
        printUsage(argv[0]);
        return 1;
    }
    
    if (helpRequested) {
        printUsage(argv[0]);
        return 0;
    }
    
    std::cout << "🔍 Directory Scanner Demo - Starting...\n";
    std::cout << "=======================================\n";
    std::cout << "📁 Target directory: " << directoryPath << std::endl;
    if (verbose) {
        std::cout << "📢 Verbose mode: enabled\n";
    }
    std::cout << std::endl;
    
    try {
        if (verbose) {
            std::cout << "⏳ Initializing directory scanner..." << std::endl;
        }
        
        DirectoryScanner scanner;
        
        if (verbose) {
            std::cout << "🔄 Starting recursive scan..." << std::endl;
        }
        
        auto files = scanner.findExcelFiles(directoryPath);
        auto stats = scanner.getLastScanStatistics();
        
        if (verbose) {
            std::cout << "✅ Scan completed, processing results..." << std::endl;
        }
        
        printResults(files, stats, verbose);
        
        // Финальный статус
        std::cout << "\n";
        if (stats.isSuccessful()) {
            std::cout << "🎉 Scan completed successfully!" << std::endl;
        } else {
            std::cout << "⚠️  Scan completed with warnings (check access errors)" << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "\n💥 Error: " << e.what() << std::endl;
        std::cerr << "Use '" << argv[0] << " --help' for usage information.\n";
        return 1;
    } catch (...) {
        std::cerr << "\n💥 Unknown error occurred during scanning\n";
        return 1;
    }
    
    return 0;
}