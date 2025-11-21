#include "DataModels.h"
#include <stdexcept>
#include <sstream>

/**
 * @brief Конструктор класса Student
 * @param name Полное имя учащегося
 * @param class_name Название класса
 * @throw std::invalid_argument Если имя или название класса пустые
 */
Student::Student(const std::string& name, const std::string& class_name) 
    : fullName(name), className(class_name), averageScore(0.0), rating(0) {
    if (name.empty() || class_name.empty()) {
        throw std::invalid_argument("Name and class name cannot be empty");
    }
}

/**
 * @brief Добавляет сырой балл по предмету
 * @param subject Название предмета
 * @param score Сырой балл
 * @throw std::invalid_argument Если название предмета пустое или балл отрицательный
 */
void Student::addSubjectScore(const std::string& subject, double score) {
    if (subject.empty()) {
        throw std::invalid_argument("Subject name cannot be empty");
    }
    if (score < 0) {
        throw std::invalid_argument("Score cannot be negative");
    }
    subjectScores[subject] = score;
}

/**
 * @brief Добавляет итоговую оценку по предмету
 * @param subject Название предмета
 * @param grade Оценка (2-5)
 * @throw std::invalid_argument Если название предмета пустое или оценка вне диапазона
 */
void Student::addSubjectGrade(const std::string& subject, int grade) {
    if (subject.empty()) {
        throw std::invalid_argument("Subject name cannot be empty");
    }
    if (grade < 2 || grade > 5) {
        throw std::invalid_argument("Grade must be between 2 and 5");
    }
    subjectGrades[subject] = grade;
}