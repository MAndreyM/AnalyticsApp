#pragma once

#include <filesystem>
#include <vector>
#include "FileMetadata.hpp"
#include "../core/Student.hpp"

/**
 * @class ITableParser
 * @brief Интерфейс для парсеров табличных данных
 * 
 * Определяет контракт для всех парсеров, которые могут
 * преобразовывать файлы в структуры данных учащихся.
 */
class ITableParser {
public:
    virtual ~ITableParser() = default;

    /**
     * @brief Парсит файл и извлекает данные учащихся
     * @param filePath Путь к файлу для парсинга
     * @return Вектор объектов Student, извлеченных из файла
     */
    virtual std::vector<Student> parse(const std::filesystem::path& filePath) = 0;

    /**
     * @brief Извлекает метаданные из файла
     * @param filePath Путь к файлу
     * @return Структура FileMetadata с метаданными файла
     */
    virtual FileMetadata extractMetadata(const std::filesystem::path& filePath) = 0;
};