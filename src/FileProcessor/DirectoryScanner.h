#pragma once

#include <string>
#include <vector>
#include <chrono>

/**
 * @brief Сканер директорий для поиска Excel файлов
 * 
 * Обеспечивает рекурсивный поиск .xls файлов в указанной директории
 * с поддержкой статистики сканирования и обработкой ошибок.
 */
class DirectoryScanner {
public:
    /**
     * @brief Конструктор по умолчанию
     */
    DirectoryScanner() = default;
    
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
     * @brief Проверяет доступ на чтение для директории
     * 
     * @param directoryPath Путь к директории
     * @return true Если директория доступна для чтения
     * @return false Если доступ запрещен
     */
    bool hasReadAccess(const std::string& directoryPath) const;
    
    /**
     * @brief Статистика сканирования
     */
    struct ScanStatistics {
        size_t totalFilesScanned = 0;    ///< Всего проверено файлов
        size_t excelFilesFound = 0;      ///< Найдено Excel файлов
        size_t directoriesScanned = 0;   ///< Отсканировано директорий
        size_t accessErrors = 0;         ///< Ошибок доступа
        std::chrono::milliseconds scanDuration{0}; ///< Время сканирования
        
        /**
         * @brief Сбрасывает статистику
         */
        void reset() {
            totalFilesScanned = 0;
            excelFilesFound = 0;
            directoriesScanned = 0;
            accessErrors = 0;
            scanDuration = std::chrono::milliseconds(0);
        }
        
        /**
         * @brief Выводит статистику в читаемом формате
         */
        void print() const {
            std::cout << "📊 Scan Statistics:\n"
                      << "   📁 Directories scanned: " << directoriesScanned << "\n"
                      << "   📄 Total files scanned: " << totalFilesScanned << "\n"
                      << "   📊 Excel files found: " << excelFilesFound << "\n"
                      << "   ⚠️  Access errors: " << accessErrors << "\n"
                      << "   ⏱️  Duration: " << scanDuration.count() << "ms\n";
        }
        
        /**
         * @brief Проверяет, было ли сканирование успешным
         */
        bool isSuccessful() const {
            return accessErrors == 0;
        }
    };
    
    /**
     * @brief Получает статистику последнего сканирования
     * 
     * @return ScanStatistics Статистика сканирования
     */
    ScanStatistics getLastScanStatistics() const { return lastStatistics_; }
    
    /**
     * @brief Получает время последнего сканирования в миллисекундах
     */
    long long getLastScanDurationMs() const { 
        return lastStatistics_.scanDuration.count(); 
    }

private:
    /**
     * @brief Валидирует входные параметры для сканирования
     * 
     * @param directoryPath Путь к директории
     * @throw std::runtime_error Если параметры невалидны
     */
    void validateInputParameters(const std::string& directoryPath) const;
    
    ScanStatistics lastStatistics_;  ///< Статистика последнего сканирования
};