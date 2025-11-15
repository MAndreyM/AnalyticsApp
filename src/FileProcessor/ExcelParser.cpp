#include "ExcelParser.h"
#include <xls.h>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <cstring>

// Вспомогательная структура для автоматического освобождения ресурсов libxls
struct WorkbookDeleter {
    void operator()(xlsWorkBook* workbook) const {
        if (workbook) {
            // TODO: Реализовать в коммите 6
            // xls_close_WB(workbook);
        }
    }
};

// Используем сырой указатель вместо unique_ptr до реализации libxls
using WorkbookPtr = xlsWorkBook*;

ExcelParser::ExcelParser() = default;

ExcelParser::~ExcelParser() = default;

Student ExcelParser::parseStudentData(const std::filesystem::path& filePath) {
    // TODO: Полная реализация будет в коммите 8
    
    std::cout << "DEBUG: parseStudentData called for: " << filePath.string() << std::endl;
    
    if (!isValidExcelFile(filePath)) {
        throw std::runtime_error("Invalid Excel file: " + filePath.string());
    }
    
    // Временная заглушка - возвращаем тестового студента
    Student student("10А", "Иванов Иван Иванович");
    student.addSubjectScore("Математика", 4.5);
    student.addSubjectScore("Физика", 3.7);
    
    std::cout << "DEBUG: Returning test student data" << std::endl;
    return student;
}

std::string ExcelParser::extractClassName(const std::string& cellA4) {
    // TODO: Полная реализация будет использовать processCellA4 из коммита 5
    
    std::cout << "DEBUG: extractClassName called with: '" << cellA4 << "'" << std::endl;
    
    // Временная базовая реализация
    return processCellA4(cellA4);
}

bool ExcelParser::isValidExcelFile(const std::filesystem::path& filePath) {
    // TODO: Полная реализация будет в коммите 5
    
    std::cout << "DEBUG: isValidExcelFile called for: " << filePath.string() << std::endl;
    
    // Временная базовая реализация
    if (!std::filesystem::exists(filePath)) {
        return false;
    }
    
    if (!std::filesystem::is_regular_file(filePath)) {
        return false;
    }
    
    std::string extension = filePath.extension().string();
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
    
    return extension == ".xls";
}

// ============================================================================
// ПРИВАТНЫЕ МЕТОДЫ - ВРЕМЕННЫЕ ЗАГЛУШКИ
// ============================================================================

WorkbookPtr ExcelParser::readExcelFile(const std::filesystem::path& filePath) {
    // TODO: Полная реализация будет в коммите 6
    
    std::cout << "DEBUG: readExcelFile called for: " << filePath.string() << std::endl;
    
    // Временная заглушка - возвращаем nullptr
    // В коммите 6 будет: xlsWorkBook* workbook = xls_open_file(filePath.string().c_str(), "UTF-8");
    
    std::cout << "DEBUG: readExcelFile - returning nullptr (stub)" << std::endl;
    return nullptr;
}

void ExcelParser::parseWorksheet(WorkbookPtr workbook, Student& student) {
    // TODO: Полная реализация будет в коммите 7
    
    std::cout << "DEBUG: parseWorksheet called" << std::endl;
    
    if (!workbook) {
        throw std::runtime_error("Workbook is null in parseWorksheet");
    }
    
    // Временная заглушка - устанавливаем тестовые данные
    // В коммите 7 будет полная реализация парсинга структуры файла
    
    student.setClassName("10А");
    student.setFullName("Тестовый Студент");
    
    std::cout << "DEBUG: parseWorksheet - setting test data" << std::endl;
}

std::string ExcelParser::extractStudentName(WorkbookPtr workbook) {
    // TODO: Полная реализация будет в коммите 7
    
    std::cout << "DEBUG: extractStudentName called" << std::endl;
    
    if (!workbook) {
        throw std::runtime_error("Workbook is null in extractStudentName");
    }
    
    // Временная заглушка - возвращаем тестовое имя
    // В коммите 7 будет извлечение из конкретной ячейки Excel
    
    std::cout << "DEBUG: extractStudentName - returning test name" << std::endl;
    return "Тестовый Студент";
}

void ExcelParser::extractSubjectScores(WorkbookPtr workbook, Student& student) {
    // TODO: Полная реализация будет в коммите 8
    
    std::cout << "DEBUG: extractSubjectScores called" << std::endl;
    
    if (!workbook) {
        throw std::runtime_error("Workbook is null in extractSubjectScores");
    }
    
    // Временная заглушка - добавляем тестовые данные
    // В коммите 8 будет парсинг таблицы предметов и оценок
    
    student.addSubjectScore("Математика", 4.5);
    student.addSubjectScore("Физика", 3.7);
    student.addSubjectScore("Химия", 4.2);
    student.addSubjectScore("Русский язык", 3.9);
    
    std::cout << "DEBUG: extractSubjectScores - added test subjects" << std::endl;
}

std::string ExcelParser::processCellA4(const std::string& content) {
    // TODO: Улучшенная реализация будет в коммите 5
    
    std::cout << "DEBUG: processCellA4 called with: '" << content << "'" << std::endl;
    
    // Временная базовая реализация
    if (content.empty()) {
        return "";
    }
    
    // Ищем первую запятую
    size_t commaPos = content.find(',');
    if (commaPos != std::string::npos) {
        // Возвращаем часть строки до запятой
        std::string className = content.substr(0, commaPos);
        // Убираем лишние пробелы
        size_t firstNonSpace = className.find_first_not_of(" \t");
        size_t lastNonSpace = className.find_last_not_of(" \t");
        
        if (firstNonSpace != std::string::npos && lastNonSpace != std::string::npos) {
            std::string result = className.substr(firstNonSpace, lastNonSpace - firstNonSpace + 1);
            std::cout << "DEBUG: processCellA4 - extracted class: '" << result << "'" << std::endl;
            return result;
        }
    }
    
    // Если запятой нет, возвращаем всю строку
    std::cout << "DEBUG: processCellA4 - no comma found, returning full content" << std::endl;
    return content;
}

void ExcelParser::cleanupWorkbook(WorkbookPtr workbook) {
    // TODO: Полная реализация будет в коммите 6
    
    std::cout << "DEBUG: cleanupWorkbook called" << std::endl;
    
    if (workbook) {
        // В коммите 6 будет: xls_close_WB(workbook);
        std::cout << "DEBUG: cleanupWorkbook - would cleanup workbook (stub)" << std::endl;
    }
}