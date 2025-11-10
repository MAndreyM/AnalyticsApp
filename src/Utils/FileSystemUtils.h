#pragma once

#include <string>
#include <vector>
#include <filesystem>

/**
 * @brief Утилиты для работы с файловой системой
 */
class FileSystemUtils {
public:
    /**
     * @brief Проверяет существование файла или директории
     */
    static bool exists(const std::string& path);
    
    /**
     * @brief Проверяет, является ли путь директорией
     */
    static bool isDirectory(const std::string& path);
    
    /**
     * @brief Создает директорию (включая родительские)
     */
    static bool createDirectory(const std::string& path);
    
    /**
     * @brief Получает расширение файла в нижнем регистре
     */
    static std::string getFileExtension(const std::string& filename);
    
    /**
     * @brief Проверяет, является ли файл Excel-файлом (.xls)
     */
    static bool isExcelFile(const std::string& filename);
    
    /**
     * @brief Получает список файлов в директории с заданным расширением
     */
    static std::vector<std::string> getFilesWithExtension(const std::string& directory, const std::string& extension);
};