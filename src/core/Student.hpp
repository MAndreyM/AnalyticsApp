#pragma once

#include "StudentCategory.hpp"

#include <string>
#include <vector>
#include <unordered_map>

/**
 * @struct Student
 * @brief Структура данных ученика
 * 
 * Содержит полную информацию об ученике: ФИО, оценки по предметам,
 * категорию успеваемости и флаги для анализа.
 */
class Student {
private:
    std::string className;                          ///< Название класса ученика
    std::string fullName;                            ///< Полное имя ученика
    std::unordered_map<std::string, double> subjectScores; ///< Исходные баллы по предметам (0-5.0)
    std::unordered_map<std::string, int> subjectGrades;    ///< Итоговые оценки по предметам (0,2-5)
    StudentCategory category;                       ///< Категория ученика по успеваемости
    bool hasZeroGrade;                              ///< Флаг наличия оценки 0
    bool isExcluded;                                ///< Флаг исключения из анализа

public:
    // Конструкторы
    Student();
    Student(const std::string& className, const std::string& fullName);

    /**
     * @brief Проверяет наличие двоек у ученика
     * @return true если есть хотя бы одна оценка 2, иначе false
     */
    bool hasGradeTwo() const;

    /**
     * @brief Проверяет наличие ровно одной оценки заданного значения
     * @param grade Значение оценки для проверки (2, 3, 4, 5)
     * @return true если есть ровно одна такая оценка, иначе false
     */
    bool hasSingleGrade(int grade) const;

    /**
     * @brief Проверяет, что все оценки ученика из заданного набора
     * @param allowedGrades Вектор разрешенных оценок
     * @return true если все оценки ученика входят в разрешенный набор, иначе false
     */
    bool hasOnlyGrades(const std::vector<int>& allowedGrades) const;

    /**
     * @brief Возвращает список предметов с заданной оценкой
     * @param grade Оценка для поиска
     * @return Вектор названий предметов с заданной оценкой
     */
    std::vector<std::string> getSubjectsWithGrade(int grade) const;

    /**
     * @brief Подсчитывает количество заданных оценок
     * @param grade Оценка для подсчета
     * @return Количество оценок с заданным значением
     */
    int countGrades(int grade) const;

    /**
     * @brief Определяет категорию ученика на основе оценок
     * @return Категория ученика (StudentCategory)
     */
    StudentCategory determineCategory() const;
};