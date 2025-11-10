#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <stdexcept>

/**
 * @brief Исключение для ошибок валидации данных
 */
class DataValidationException : public std::runtime_error {
public:
    explicit DataValidationException(const std::string& message) 
        : std::runtime_error(message) {}
};

/**
 * @brief Модель данных учащегося с валидацией
 */
class Student {
private:
    std::string className_;
    std::string fullName_;
    std::string lastName_;
    std::string firstName_; 
    std::string middleName_;
    
    std::unordered_map<std::string, double> subjectScores_;
    std::unordered_map<std::string, int> subjectGrades_;
    
    double averageScore_ = 0.0;
    int rating_ = 0;

    void validateData() const;

public:
    // Конструкторы
    Student() = default;
    Student(const std::string& className, const std::string& fullName);
    
    // Геттеры
    const std::string& getClassName() const { return className_; }
    const std::string& getFullName() const { return fullName_; }
    const std::string& getLastName() const { return lastName_; }
    const std::string& getFirstName() const { return firstName_; }
    const std::string& getMiddleName() const { return middleName_; }
    double getAverageScore() const { return averageScore_; }
    int getRating() const { return rating_; }
    const std::unordered_map<std::string, double>& getSubjectScores() const { return subjectScores_; }
    const std::unordered_map<std::string, int>& getSubjectGrades() const { return subjectGrades_; }
    
    // Сеттеры с валидацией
    void setClassName(const std::string& className);
    void setFullName(const std::string& fullName);
    void addSubjectScore(const std::string& subject, double score);
    void setSubjectGrade(const std::string& subject, int grade);  // ← ДОБАВЛЕНО
    void setAverageScore(double score);
    void setRating(int rating);
    
    // Валидация
    bool isValid() const;
    
    // Утилиты
    bool hasSubject(const std::string& subject) const;
    double getSubjectScore(const std::string& subject) const;
    int getSubjectGrade(const std::string& subject) const;
};

/**
 * @brief Результат анализа данных
 */
class AnalysisResult {
private:
    std::vector<std::pair<std::string, Student>> studentsWithSingleThree_;
    std::vector<std::pair<std::string, Student>> studentsWithZeroScore_;

public:
    // Добавление результатов
    void addStudentWithSingleThree(const std::string& subject, const Student& student);
    void addStudentWithZeroScore(const std::string& subject, const Student& student);
    
    // Геттеры
    const std::vector<std::pair<std::string, Student>>& getStudentsWithSingleThree() const { 
        return studentsWithSingleThree_; 
    }
    const std::vector<std::pair<std::string, Student>>& getStudentsWithZeroScore() const { 
        return studentsWithZeroScore_; 
    }
    
    // Утилиты
    size_t countStudentsWithSingleThree() const { return studentsWithSingleThree_.size(); }
    size_t countStudentsWithZeroScore() const { return studentsWithZeroScore_.size(); }
    void clear();
};

/**
 * @brief Утилиты для работы со строками
 */
class StringUtils {
public:
    static std::string trim(const std::string& str);
    static std::vector<std::string> split(const std::string& str, char delimiter);
    static bool endsWith(const std::string& str, const std::string& suffix);
    static std::string toLower(const std::string& str);
    static bool isValidName(const std::string& name);
};