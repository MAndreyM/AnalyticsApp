// Заглушка для AnalyticsCore - Student.hpp
#pragma once

#include <string>

class Student {
private:
    std::string name;
public:
    Student() = default;
    explicit Student(const std::string& n) : name(n) {}
    std::string getName() const { return name; }
};
