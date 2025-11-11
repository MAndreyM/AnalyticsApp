#include "DirectoryScanner.h"
#include <stdexcept>

std::vector<std::string> DirectoryScanner::findExcelFiles(const std::string& directoryPath) {
    // TODO: Реализовать рекурсивное сканирование директории
    // TODO: Интегрировать с ExcelFileFilter
    // TODO: Обновлять статистику сканирования
    
    lastStatistics_.reset();
    
    // Заглушка - возвращаем пустой список
    return std::vector<std::string>();
}

std::vector<std::string> DirectoryScanner::findExcelFiles(const std::string& directoryPath, int maxDepth) {
    // TODO: Реализовать сканирование с ограничением глубины
    // Временная реализация - используем базовый метод
    return findExcelFiles(directoryPath);
}