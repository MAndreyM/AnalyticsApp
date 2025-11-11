#include "DirectoryScanner.h"
#include "ExcelFileFilter.h"
#include <stdexcept>
#include <filesystem>

std::vector<std::string> DirectoryScanner::findExcelFiles(const std::string& directoryPath) {
    // Сбрасываем статистику перед новым сканированием
    lastStatistics_.reset();
    
    auto startTime = std::chrono::high_resolution_clock::now();
    
    try {
        // Валидация входных параметров
        validateInputParameters(directoryPath);
        
        // Используем ExcelFileFilter для рекурсивного поиска
        auto files = ExcelFileFilter::findExcelFilesRecursive(directoryPath);
        
        // Обновляем статистику
        lastStatistics_.excelFilesFound = files.size();
        
        // Подсчитываем общее количество файлов и директорий
        try {
            for (const auto& entry : std::filesystem::recursive_directory_iterator(
                    directoryPath, 
                    std::filesystem::directory_options::skip_permission_denied)) {
                
                if (entry.is_regular_file()) {
                    lastStatistics_.totalFilesScanned++;
                } else if (entry.is_directory()) {
                    lastStatistics_.directoriesScanned++;
                }
            }
        } catch (const std::filesystem::filesystem_error& e) {
            // Логируем, но не прерываем выполнение - у нас уже есть результаты
            lastStatistics_.accessErrors++;
            std::cerr << "Warning: Partial filesystem error during statistics: " 
                      << e.what() << std::endl;
        }
        
        auto endTime = std::chrono::high_resolution_clock::now();
        lastStatistics_.scanDuration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
        
        return files;
        
    } catch (const std::exception& e) {
        // Увеличиваем счетчик ошибок и вычисляем время
        lastStatistics_.accessErrors++;
        auto endTime = std::chrono::high_resolution_clock::now();
        lastStatistics_.scanDuration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
        
        throw std::runtime_error("Directory scanning failed: " + std::string(e.what()));
    }
}

std::vector<std::string> DirectoryScanner::findExcelFiles(const std::string& directoryPath, int maxDepth) {
    // Временная реализация - используем базовый метод без ограничения глубины
    // TODO: В будущем добавить поддержку maxDepth с кастомным итератором
    if (maxDepth <= 0) {
        throw std::runtime_error("Max depth must be positive");
    }
    
    return findExcelFiles(directoryPath);
}

bool DirectoryScanner::hasReadAccess(const std::string& directoryPath) const {
    try {
        // Простая проверка - пытаемся создать directory_iterator
        std::filesystem::directory_iterator it(directoryPath);
        return true;
    } catch (const std::filesystem::filesystem_error&) {
        return false;
    }
}

void DirectoryScanner::validateInputParameters(const std::string& directoryPath) const {
    // Проверка на пустой путь
    if (directoryPath.empty()) {
        throw std::runtime_error("Directory path cannot be empty");
    }
    
    // Проверка существования
    if (!std::filesystem::exists(directoryPath)) {
        throw std::runtime_error("Directory does not exist: " + directoryPath);
    }
    
    // Проверка что это директория
    if (!std::filesystem::is_directory(directoryPath)) {
        throw std::runtime_error("Path is not a directory: " + directoryPath);
    }
    
    // Проверка прав доступа (базовая)
    if (!hasReadAccess(directoryPath)) {
        throw std::runtime_error("No read access to directory: " + directoryPath);
    }
}