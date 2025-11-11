#pragma once

#include <string>
#include <vector>

/**
 * @brief Фильтр для Excel файлов с поддержкой рекурсивного поиска
 * 
 * Обеспечивает проверку файлов на соответствие формату Excel (.xls)
 * и рекурсивный поиск в файловой системе.
 */
class ExcelFileFilter {
public:
    /**
     * @brief Находит все Excel файлы в директории (рекурсивно)
     * 
     * @param directoryPath Путь к директории для сканирования
     * @return std::vector<std::string> Список путей к найденным .xls файлам
     * @throw std::runtime_error Если произошла ошибка файловой системы
     */
    static std::vector<std::string> findExcelFilesRecursive(const std::string& directoryPath);
    
    /**
     * @brief Проверяет, является ли файл Excel файлом (.xls)
     * 
     * @param filePath Путь к файлу для проверки
     * @return true Если файл имеет расширение .xls (регистронезависимо)
     * @return false Если файл не существует или не является .xls
     */
    static bool isExcelFile(const std::string& filePath);
    
    /**
     * @brief Нормализует расширение файла (приводит к нижнему регистру)
     * 
     * @param extension Расширение файла
     * @return std::string Нормализованное расширение в нижнем регистре
     */
    static std::string normalizeExtension(const std::string& extension);

private:
    /**
     * @brief Рекурсивно сканирует директорию
     * 
     * @param directoryPath Путь к директории для сканирования
     * @param excelFiles Вектор для сохранения найденных Excel файлов
     */
    static void scanDirectoryRecursive(const std::string& directoryPath, 
                                      std::vector<std::string>& excelFiles);
};