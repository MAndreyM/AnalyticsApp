#include "ExcelFileFilter.h"
#include <stdexcept>

std::vector<std::string> ExcelFileFilter::findExcelFilesRecursive(const std::string& directoryPath) {
    // TODO: Реализовать рекурсивное сканирование директории
    // TODO: Обработка ошибок файловой системы
    // TODO: Поддержка skip_permission_denied
    
    std::vector<std::string> excelFiles;
    // Временная заглушка
    return excelFiles;
}

bool ExcelFileFilter::isExcelFile(const std::string& filePath) {
    // TODO: Реализовать проверку расширения .xls
    // TODO: Сделать регистронезависимую проверку
    // TODO: Добавить проверку существования файла
    
    return false; // Временная заглушка
}

std::string ExcelFileFilter::normalizeExtension(const std::string& extension) {
    // TODO: Реализовать нормализацию расширения
    // Привести к нижнему регистру, убрать лишние точки
    
    return extension; // Временная заглушка
}

void ExcelFileFilter::scanDirectoryRecursive(const std::string& directoryPath, 
                                           std::vector<std::string>& excelFiles) {
    // TODO: Реализовать рекурсивное сканирование
    // TODO: Использовать std::filesystem::recursive_directory_iterator
    // TODO: Обработка ошибок доступа
}