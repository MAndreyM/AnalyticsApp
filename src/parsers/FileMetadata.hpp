// TODO: Реализовать FileMetadata
#pragma once

#include <string>

/**
 * @struct FileMetadata
 * @brief Структура для хранения метаданных файла
 * 
 * Содержит информацию о файле: название класса,
 * учебный год, дату экспорта и другие метаданные.
 */
struct FileMetadata {
    std::string className;      ///< Название класса (например, "10А")
    std::string academicYear;   ///< Учебный год (например, "2025/2026 учебный год")
    std::string exportDate;     ///< Дата экспорта (например, "25.12.2025")

    // TODO: Добавить другие метаданные по мере необходимости

    /**
     * @brief Проверяет, заполнены ли основные поля метаданных
     * @return true если className не пустой, иначе false
     */
    bool isValid() const {
        return !className.empty();
    }
};