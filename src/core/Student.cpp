// Заглушка для AnalyticsCore - Student.cpp
#include "Student.hpp"

#include <algorithm>

bool Student::hasGradeTwo() const {
    for (const auto& [subject, grade] : subjectGrades) {
        if (grade == 2) {
            return true;
        }
    }
    return false;
}

int Student::countGrades(int grade) const {
    int count = 0;
    for (const auto& [subject, studentGrade] : subjectGrades) {
        if (studentGrade == grade) {
            count++;
        }
    }
    return count;
}

std::vector<std::string> Student::getSubjectsWithGrade(int grade) const {
    std::vector<std::string> subjects;
    for (const auto& [subject, studentGrade] : subjectGrades) {
        if (studentGrade == grade) {
            subjects.push_back(subject);
        }
    }
    return subjects;
}

bool Student::hasSingleGrade(int grade) const {
    int count = 0;
    for (const auto& [subject, studentGrade] : subjectGrades) {
        if (studentGrade == grade) {
            count++;
            if (count > 1) {
                return false;
            }
        }
    }
    return count == 1;
}

bool Student::hasOnlyGrades(const std::vector<int>& allowedGrades) const {
    for (const auto& [subject, grade] : subjectGrades) {
        if (std::find(allowedGrades.begin(), allowedGrades.end(), grade) == allowedGrades.end()) {
            return false;
        }
    }
    return true;
}

StudentCategory Student::determineCategory() const {
    // TODO: Реализовать алгоритм определения категории согласно ТЗ
    // 1. Проверить наличие оценки 0 → ZERO_GRADE
    // 2. Проверить наличие двоек → HAS_TWOS
    // 3. Проверить одну тройку при остальных 4/5 → SINGLE_THREE
    // 4. Проверить одну четверку при остальных 5 → SINGLE_FOUR
    // 5. Проверить только 4 и 5 → FOURS_AND_FIVES
    // 6. Проверить только 5 → EXCELLENT
    // 7. Иначе → REGULAR

    return StudentCategory::REGULAR; // Временная заглушка
}
