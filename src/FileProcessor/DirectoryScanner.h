#pragma once

#include <string>
#include <vector>

/**
 * @brief Сканер директорий для поиска Excel файлов
 * 
 * Обеспечивает рекурсивный поиск .xls файлов в указанной директории
 * с поддержкой статистики сканирования и обработкой ошибок.
 */
class DirectoryScanner {
public:
    /**
     * @brief Находит все Excel файлы в указанной директории (рекурсивно)
     * 
     * @param directoryPath Путь к директории для сканирования
     * @return std::vector<std::string> Список путей к найденным .xls файлам
     * @throw std::runtime_error Если директория не существует или недоступна
     */
    std::vector<std::string> findExcelFiles(const std::string& directoryPath);
    
    /**
     * @brief Находит Excel файлы с ограничением глубины рекурсии
     * 
     * @param directoryPath Путь к директории для сканирования
     * @param maxDepth Максимальная глубина рекурсии
     * @return std::vector<std::string> Список путей к найденным .xls файлам
     */
    std::vector<std::string> findExcelFiles(const std::string& directoryPath, int maxDepth);
    
    /**
     * @brief Статистика сканирования
     */
    struct ScanStatistics {
        size_t totalFilesFound = 0;      ///< Всего найдено файлов
        size_t excelFilesFound = 0;      ///< Найдено Excel файлов
        size_t directoriesScanned = 0;   ///< Отсканировано директорий
        size_t accessErrors = 0;         ///< Ошибок доступа
        
        /**
         * @brief Сбрасывает статистику
         */
        void reset() {
            totalFilesFound = 0;
            excelFilesFound = 0;
            directoriesScanned = 0;
            accessErrors = 0;
        }
        
        /**
         * @brief Выводит статистику в читаемом формате
         */
        void print() const {
            std::cout << "Scan Statistics:\n"
                      << "  Excel files found: " << excelFilesFound << "\n"
                      << "  Access errors: " << accessErrors << "\n";
        }
    };
    
    /**
     * @brief Получает статистику последнего сканирования
     * 
     * @return ScanStatistics Статистика сканирования
     */
    ScanStatistics getLastScanStatistics() const { return lastStatistics_; }

private:
    ScanStatistics lastStatistics_;  ///< Статистика последнего сканирования
};