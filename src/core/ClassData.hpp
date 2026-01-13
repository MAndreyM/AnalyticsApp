#pragma once

#include "Student.hpp"

#include <string>
#include <vector>

/**
 * @struct ClassData
 * @brief Структура данных класса
 * 
 * Содержит информацию о классе: название, список учеников,
 * предметы и результаты анализа по категориям.
 */
struct ClassData {
    std::string className;          ///< Название класса (например, "10А")
    int gradeNumber;               ///< Номер параллели (например, 10)
    std::string classLetter;       ///< Буква класса (например, "А")
    std::vector<Student> students; ///< Список учеников класса
    std::vector<std::string> subjects; ///< Список предметов класса

    /**
     * @brief Получает общее количество учеников в классе
     * @return Количество учеников
     */
    int getTotalStudents() const { return static_cast<int>(students.size()); }

    /**
     * @brief Получает количество учеников, подлежащих анализу
     * @return Количество учеников минус те, у кого есть оценки 0
     */
    int getAnalyzedStudents() const { 
        return static_cast<int>(students.size() - studentsWithZero.size()); 
    }

    // Результаты анализа
    std::vector<Student> studentsWithZero;                          ///< Ученики без оценок (имеют 0)
    std::vector<std::pair<Student, std::string>> studentsWithTwos;  ///< Ученики с двойками и предметами
    std::vector<std::pair<Student, std::string>> studentsWithSingleThree;  ///< Ученики с одной тройкой
    std::vector<std::pair<Student, std::string>> studentsWithSingleFour;   ///< Ученики с одной четверкой
    std::vector<Student> studentsWithFoursAndFives;                ///< Ученики с оценками 4 и 5
    std::vector<Student> excellentStudents;                        ///< Отличники
};