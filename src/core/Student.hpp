// Заглушка для AnalyticsCore - Student.hpp
#pragma once

#include "StudentCategory.hpp"

#include <string>
#include <vector>
#include <unordered_map>

struct Student {
    std::string fullName;
    std::string className;
    std::unordered_map<std::string, double> subjectScores;
    std::unordered_map<std::string, int> subjectGrades;
    StudentCategory category;
    bool hasZeroGrade;
    bool isExcluded;

    bool hasGradeTwo() const;
    bool hasSingleGrade(int grade) const;
    bool hasOnlyGrades(const std::vector<int>& allowedGrades) const;
    std::vector<std::string> getSubjectsWithGrade(int grade) const;
    int countGrades(int grade) const;
    StudentCategory determineCategory() const;
};