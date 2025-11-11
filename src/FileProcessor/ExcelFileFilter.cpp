#include "ExcelFileFilter.h"
#include <iostream>
#include <algorithm>
#include <cctype>

std::vector<std::string> ExcelFileFilter::findExcelFilesRecursive(const std::string& directoryPath) {
    std::vector<std::string> excelFiles;
    
    // Проверка существования директории
    if (!std::filesystem::exists(directoryPath)) {
        throw std::runtime_error("Directory does not exist: " + directoryPath);
    }
    
    // Проверка что это директория
    if (!std::filesystem::is_directory(directoryPath)) {
        throw std::runtime_error("Path is not a directory: " + directoryPath);
    }
    
    try {
        scanDirectoryRecursive(directoryPath, excelFiles);
    } catch (const std::filesystem::filesystem_error& e) {
        throw std::runtime_error("Filesystem error while scanning directory: " + std::string(e.what()));
    } catch (const std::exception& e) {
        throw std::runtime_error("Unexpected error during directory scanning: " + std::string(e.what()));
    }
    
    return excelFiles;
}

bool ExcelFileFilter::isExcelFile(const std::filesystem::path& filePath) {
    // Только проверка расширения, без проверки существования файла
    // Это позволяет тестировать метод без создания реальных файлов
    
    std::string extension = filePath.extension().string();
    std::string normalizedExtension = normalizeExtension(extension);
    
    return normalizedExtension == ".xls";
}

std::string ExcelFileFilter::normalizeExtension(const std::string& extension) {
    if (extension.empty()) {
        return extension;
    }
    
    std::string result = extension;
    
    // Приводим к нижнему регистру
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    
    return result;
}

void ExcelFileFilter::scanDirectoryRecursive(const std::filesystem::path& directoryPath, 
                                           std::vector<std::string>& excelFiles) {
    try {
        // Используем recursive_directory_iterator с обработкой ошибок доступа
        for (const auto& entry : std::filesystem::recursive_directory_iterator(
                directoryPath, 
                std::filesystem::directory_options::skip_permission_denied)) {
            
            if (entry.is_regular_file() && isExcelFile(entry.path())) {
                excelFiles.push_back(entry.path().string());
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        // Логируем ошибку и пробрасываем исключение дальше
        std::cerr << "Warning: Filesystem error during scanning - " 
                  << e.path1().string() << " - " << e.what() << std::endl;
        throw;
    }
}