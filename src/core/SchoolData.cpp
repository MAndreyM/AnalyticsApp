#include "SchoolData.hpp"
#include <algorithm>
#include <set>

std::vector<int> SchoolData::getAvailableGrades() const {
    std::set<int> grades;
    for (const auto& [className, classData] : classes) {
        grades.insert(classData.gradeNumber);
    }
    return std::vector<int>(grades.begin(), grades.end());
}

std::vector<ClassData> SchoolData::getGradeParallel(int grade) const {
    std::vector<ClassData> result;
    for (const auto& [className, classData] : classes) {
        if (classData.gradeNumber == grade) {
            result.push_back(classData);
        }
    }
    return result;
}

std::vector<std::string> SchoolData::getClassesInGrade(int grade) const {
    std::vector<std::string> classNames;
    for (const auto& [className, classData] : classes) {
        if (classData.gradeNumber == grade) {
            classNames.push_back(className);
        }
    }
    return classNames;
}

SchoolSummaryView SchoolData::getSchoolSummary() const {
    // TODO: Реализовать агрегацию данных по всем классам
    // Нужно пройти по всем классам и суммировать:
    // - studentsWithZero, studentsWithTwos и т.д.
    // - totalStudents

    SchoolSummaryView summary;
    summary.totalStudents = 0;
    summary.studentsWithZero = 0;
    summary.studentsWithTwos = 0;
    summary.studentsWithSingleThree = 0;
    summary.studentsWithSingleFour = 0;
    summary.studentsWithFoursAndFives = 0;
    summary.excellentStudents = 0;

    return summary; // Временная заглушка
}
