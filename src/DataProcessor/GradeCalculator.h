#pragma once

#include "DataModels.h"
#include <vector>

/**
 * @brief Калькулятор для анализа успеваемости учащихся
 */
class GradeCalculator {
public:
    /**
     * @brief Преобразует средний балл в оценку по правилам округления
     */
    int calculateGrade(double averageScore) const;
    
    /**
     * @brief Рассчитывает оценки для всех предметов ученика
     */
    void calculateAllGrades(Student& student) const;
    
    /**
     * @brief Проверяет, есть ли у ученика только одна тройка
     */
    bool hasSingleThree(const Student& student) const;
    
    /**
     * @brief Проверяет, есть ли у ученика хотя бы один нулевой балл
     */
    bool hasZeroScore(const Student& student) const;
    
    /**
     * @brief Анализирует список учеников и возвращает результаты
     */
    AnalysisResult analyzeStudents(const std::vector<Student>& students) const;
    
    /**
     * @brief Анализирует группу учеников (класс)
     */
    AnalysisResult analyzeClass(const std::vector<Student>& students) const;
};