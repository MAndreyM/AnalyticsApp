#pragma once

#include "../DataProcessor/DataModels.h"
#include <string>
#include <vector>
#include <memory>
#include <filesystem>

// Forward declaration для структур libxls
struct xlsWorkBook;
struct xlsWorkSheet;

// Используем сырой указатель вместо unique_ptr для неполного типа
using WorkbookPtr = xlsWorkBook*;

/**
 * @brief Парсер Excel файлов для извлечения данных учащихся
 * 
 * Обеспечивает чтение XLS файлов, извлечение информации о классе,
 * ФИО ученика и оценках по предметам с использованием библиотеки libxls.
 */
class ExcelParser {
public:
    /**
     * @brief Конструктор по умолчанию
     */
    ExcelParser();
    
    /**
     * @brief Деструктор
     */
    ~ExcelParser();
    
    /**
     * @brief Парсит данные ученика из XLS файла
     * 
     * @param filePath Путь к XLS файлу
     * @return Student Объект студента с заполненными данными
     * @throw std::runtime_error Если файл не существует, невалиден или произошла ошибка парсинга
     */
    Student parseStudentData(const std::filesystem::path& filePath);
    
    /**
     * @brief Извлекает название класса из содержимого ячейки A4
     * 
     * @param cellA4 Содержимое ячейки A4 (формат: "Класс, ФИО преподавателя")
     * @return std::string Название класса (символы до первой запятой)
     */
    std::string extractClassName(const std::string& cellA4);
    
    /**
     * @brief Проверяет валидность Excel файла
     * 
     * @param filePath Путь к файлу для проверки
     * @return true Если файл существует, является обычным файлом и имеет расширение .xls
     * @return false Если файл невалиден
     */
    bool isValidExcelFile(const std::filesystem::path& filePath);

private:
    /**
     * @brief Читает сырые данные из Excel файла
     * 
     * @param filePath Путь к Excel файлу
     * @return WorkbookPtr Указатель на структуру workbook libxls
     * @throw std::runtime_error Если не удалось прочитать файл
     */
    WorkbookPtr readExcelFile(const std::filesystem::path& filePath);
    
    /**
     * @brief Парсит данные из рабочего листа Excel
     * 
     * @param workbook Указатель на workbook libxls
     * @param student Ссылка на объект студента для заполнения
     * @throw std::runtime_error Если структура файла не соответствует ожидаемой
     */
    void parseWorksheet(WorkbookPtr workbook, Student& student);
    
    /**
     * @brief Извлекает ФИО ученика из рабочей книги
     * 
     * @param workbook Указатель на workbook libxls
     * @return std::string ФИО ученика
     * @throw std::runtime_error Если ФИО не найдено
     */
    std::string extractStudentName(WorkbookPtr workbook);
    
    /**
     * @brief Извлекает предметы и оценки из рабочей книги
     * 
     * @param workbook Указатель на workbook libxls
     * @param student Ссылка на объект студента для заполнения
     */
    void extractSubjectScores(WorkbookPtr workbook, Student& student);
    
    /**
     * @brief Обрабатывает содержимое ячейки A4 для извлечения названия класса
     * 
     * @param content Содержимое ячейки A4
     * @return std::string Название класса
     */
    std::string processCellA4(const std::string& content);
    
    /**
     * @brief Освобождает ресурсы workbook libxls
     * 
     * @param workbook Указатель на workbook для освобождения
     */
    void cleanupWorkbook(WorkbookPtr workbook);
};