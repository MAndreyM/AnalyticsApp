#pragma once

#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

#include "ClassData.hpp"
#include "SchoolSummaryView.hpp"

class SchoolData {
private:
    std::map<std::string, ClassData> classes;
    
public:
    std::vector<int> getAvailableGrades() const;
    
    // Получить все классы определенной параллели
    std::vector<ClassData> getGradeParallel(int grade) const;
    
    // Для тестирования и работы с данными
    const std::map<std::string, ClassData>& getClasses() const { return classes; }
    
    // Метод для добавления/обновления класса
    void addOrUpdateClass(const std::string& className, const ClassData& classData) {
        classes[className] = classData;
    }
    
    // Очистка данных
    void clear() {
        classes.clear();
    }

    std::vector<std::string> getClassesInGrade(int grade) const;
    SchoolSummaryView getSchoolSummary() const;

};