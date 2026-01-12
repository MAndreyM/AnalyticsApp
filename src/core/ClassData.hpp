#pragma once

#include "Student.hpp"

#include <string>
#include <vector>

struct ClassData {
    std::string className;
    int gradeNumber;
    std::string classLetter;
    std::vector<Student> students;
    std::vector<std::string> subjects;

    int getTotalStudents() const { return static_cast<int>(students.size()); }

        // Результаты анализа
    std::vector<Student> studentsWithZero;
    std::vector<std::pair<Student, std::string>> studentsWithTwos;
    std::vector<std::pair<Student, std::string>> studentsWithSingleThree;
    std::vector<std::pair<Student, std::string>> studentsWithSingleFour;
    std::vector<Student> studentsWithFoursAndFives;
    std::vector<Student> excellentStudents;

    int getAnalyzedStudents() const { 
        return static_cast<int>(students.size() - studentsWithZero.size()); 
    }

};