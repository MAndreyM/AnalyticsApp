#include "DirectoryScanner.h"
#include "ExcelFileFilter.h"
#include <stdexcept>

std::vector<std::string> DirectoryScanner::findExcelFiles(const std::string& directoryPath) {
    // Сбрасываем статистику перед новым сканированием
    lastStatistics_.reset();
    
    try {
        // Используем ExcelFileFilter для рекурсивного поиска
        auto files = ExcelFileFilter::findExcelFilesRecursive(directoryPath);
        
        // Обновляем статистику
        lastStatistics_.excelFilesFound = files.size();
        
        return files;
    } catch (const std::exception& e) {
        // Увеличиваем счетчик ошибок
        lastStatistics_.accessErrors++;
        throw std::runtime_error("Directory scanning failed: " + std::string(e.what()));
    }
}

std::vector<std::string> DirectoryScanner::findExcelFiles(const std::string& directoryPath, int maxDepth) {
    // Временная реализация - используем базовый метод без ограничения глубины
    // TODO: В будущем добавить поддержку maxDepth
    return findExcelFiles(directoryPath);
}