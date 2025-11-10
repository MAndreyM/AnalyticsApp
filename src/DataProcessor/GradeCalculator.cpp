#include "GradeCalculator.h"
#include <cmath>
#include <algorithm>

int GradeCalculator::calculateGrade(double averageScore) const {
    if (averageScore < 0) {
        return 2; // Минимальная оценка
    }
    
    if (averageScore > 5.0) {
        averageScore = 5.0; // Максимальный балл
    }
    
    double fractionalPart = averageScore - std::floor(averageScore);
    int baseGrade = static_cast<int>(std::floor(averageScore));
    
    if (fractionalPart >= 0.6) {
        return (baseGrade < 5) ? baseGrade + 1 : 5;
    } else {
        return (baseGrade >= 2) ? baseGrade : 2;
    }
}

void GradeCalculator::calculateAllGrades(Student& student) const {
    for (const auto& [subject, score] : student.getSubjectScores()) {
        int grade = calculateGrade(score);
        student.setSubjectGrade(subject, grade);  // ← ИСПОЛЬЗУЕМ НОВЫЙ МЕТОД
    }
}

bool GradeCalculator::hasSingleThree(const Student& student) const {
    int threeCount = 0;
    
    for (const auto& [subject, score] : student.getSubjectScores()) {
        int grade = calculateGrade(score);
        if (grade == 3) {
            threeCount++;
        }
    }
    
    return threeCount == 1;
}

bool GradeCalculator::hasZeroScore(const Student& student) const {
    for (const auto& [subject, score] : student.getSubjectScores()) {
        if (score == 0.0) {
            return true;
        }
    }
    return false;
}

AnalysisResult GradeCalculator::analyzeStudents(const std::vector<Student>& students) const {
    AnalysisResult result;
    
    for (const auto& student : students) {
        // Проверяем критерий одной тройки
        if (hasSingleThree(student)) {
            // Находим предмет с тройкой
            for (const auto& [subject, score] : student.getSubjectScores()) {
                if (calculateGrade(score) == 3) {
                    result.addStudentWithSingleThree(subject, student);
                    break;
                }
            }
        }
        
        // Проверяем критерий нулевого балла
        if (hasZeroScore(student)) {
            // Находим предметы с нулевым баллом
            for (const auto& [subject, score] : student.getSubjectScores()) {
                if (score == 0.0) {
                    result.addStudentWithZeroScore(subject, student);
                }
            }
        }
    }
    
    return result;
}

AnalysisResult GradeCalculator::analyzeClass(const std::vector<Student>& students) const {
    return analyzeStudents(students);
}