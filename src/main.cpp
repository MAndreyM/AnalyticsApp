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
 * @brief Выводит главное меню приложения
 */
void printMainMenu() {
    std::cout << "\n🎯 AnalyticsApp - Main Menu\n";
    std::cout << "===========================\n";
    std::cout << "1. 📊 Analyze student data\n";
    std::cout << "2. 🔍 Scan directory for Excel files\n";
    std::cout << "3. 📁 Check file system utilities\n";
    std::cout << "4. 🚪 Exit\n";
    std::cout << "===========================\n";
    std::cout << "Select option (1-4): ";
}

/**
 * @brief Демонстрация анализа данных студентов
 */
void demonstrateDataAnalysis() {
    std::cout << "\n📊 Student Data Analysis Demo\n";
    std::cout << "============================\n";
    
    Student student1("10A", "Иванов Иван Иванович");
    Student student2("10B", "Петрова Анна Сергеевна");
    
    std::cout << "Created sample students:\n";
    std::cout << "  " << student1.getFullName() << " (" << student1.getClassName() << ")\n";
    std::cout << "  " << student2.getFullName() << " (" << student2.getClassName() << ")\n";
    
    std::cout << "\n📈 Grade Calculator Features:\n";
    std::cout << "  - Grade rounding logic (≥ 0.6 → round up)\n";
    std::cout << "  - Performance analysis\n";
    std::cout << "  - 4 comprehensive test scenarios\n";
    
    std::cout << "\n💡 Run './bin/demo_datamodels' for full data models demonstration\n";
    std::cout << "💡 Run './test_gradecalculator' for comprehensive test scenarios\n";
}

/**
 * @brief Демонстрация сканирования директории
 */
void demonstrateDirectoryScanning() {
    std::cout << "\n🔍 Directory Scanning Demo\n";
    std::cout << "=========================\n";
    
    std::string directoryPath;
    std::cout << "Enter directory path to scan (or press Enter for './test_data'): ";
    std::getline(std::cin, directoryPath);
    
    if (directoryPath.empty()) {
        directoryPath = "./test_data";
    }
    
    try {
        DirectoryScanner scanner;
        
        std::cout << "⏳ Scanning directory: " << directoryPath << "\n";
        auto files = scanner.findExcelFiles(directoryPath);
        auto stats = scanner.getLastScanStatistics();
        
        std::cout << "\n🎯 Scan Results:\n";
        if (!files.empty()) {
            std::cout << "✅ Found " << files.size() << " Excel file(s):\n";
            for (size_t i = 0; i < files.size(); ++i) {
                std::cout << "   " << (i + 1) << ". " << files[i] << "\n";
            }
        } else {
            std::cout << "❌ No Excel files found with .xls extension\n";
        }
        
        std::cout << "\n";
        stats.print();
        
    } catch (const std::exception& e) {
        std::cout << "💥 Error: " << e.what() << "\n";
        std::cout << "💡 Tip: Create a 'test_data' directory with some .xls files for testing\n";
    }
}

/**
 * @brief Демонстрация утилит файловой системы
 */
void demonstrateFileSystemUtilities() {
    std::cout << "\n📁 File System Utilities Demo\n";
    std::cout << "============================\n";
    
    std::string testPath;
    std::cout << "Enter file/directory path to check (or press Enter for current directory): ";
    std::getline(std::cin, testPath);
    
    if (testPath.empty()) {
        testPath = ".";
    }
    
    try {
        std::cout << "📊 File System Information:\n";
        std::cout << "  Path: " << testPath << "\n";
        
        bool exists = std::filesystem::exists(testPath);
        std::cout << "  Exists: " << (exists ? "✅ Yes" : "❌ No") << "\n";
        
        if (exists) {
            bool is_file = std::filesystem::is_regular_file(testPath);
            bool is_dir = std::filesystem::is_directory(testPath);
            
            std::cout << "  Is file: " << (is_file ? "📄 Yes" : "❌ No") << "\n";
            std::cout << "  Is directory: " << (is_dir ? "📁 Yes" : "❌ No") << "\n";
            
            if (is_file) {
                std::filesystem::path path(testPath);
                std::string extension = path.extension().string();
                std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
                
                std::cout << "  Is Excel file: " << (extension == ".xls" ? "📊 Yes" : "❌ No") << "\n";
                
                try {
                    auto size = std::filesystem::file_size(testPath);
                    std::cout << "  File size: " << size << " bytes\n";
                } catch (const std::exception& e) {
                    std::cout << "  File size: ❌ Unable to determine\n";
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
                        if (fileCount + dirCount > 10) break; // Ограничиваем вывод
                    }
                    std::cout << "  Files: " << fileCount << ", Directories: " << dirCount << " (showing first 10 items)\n";
                } catch (const std::exception& e) {
                    std::cout << "  Directory contents: ❌ Unable to list\n";
                }
            }
        }
        
    } catch (const std::exception& e) {
        std::cout << "💥 Error: " << e.what() << "\n";
    }
}

/**
 * @brief Основная функция приложения
 */
int main() {
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
            std::cout << "❌ Invalid input. Please enter a number 1-4.\n";
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
                std::cout << "❌ Invalid option. Please select 1-4.\n";
                break;
        }
        
        if (running && choice != 4) {
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
        }
    }
    
    return 0;
}