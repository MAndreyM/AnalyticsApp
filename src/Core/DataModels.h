#ifndef DATAMODELS_H
#define DATAMODELS_H

#include <string>
#include <unordered_map>

/**
 * @class Student
 * @brief Модель данных учащегося с академической информацией
 */
class Student {
public:
    // Основная информация
    std::string className;
    std::string fullName;
    
    // Академические данные
    std::unordered_map<std::string, double> subjectScores;  // Сырые баллы по предметам
    std::unordered_map<std::string, int> subjectGrades;     // Итоговые оценки по предметам
    double averageScore;                                    // Средний балл
    int rating;                                             // Рейтинг в классе
    
    // Конструкторы
    Student() = default;
    explicit Student(const std::string& name, const std::string& class_name);
    
    // Методы управления данными
    void addSubjectScore(const std::string& subject, double score);
    void addSubjectGrade(const std::string& subject, int grade);
    double calculateAverageScore() const;
    bool hasSubject(const std::string& subject) const;
    void clearData();
    
    // Сериализация
    std::string toString() const;
};

#endif // DATAMODELS_H