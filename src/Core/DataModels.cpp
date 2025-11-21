#include "DataModels.h"
#include <stdexcept>
#include <sstream>

// ... предыдущий код ...

/**
 * @brief Вычисляет средний балл по всем предметам
 * @return Средний балл или 0.0 если нет предметов
 */
double Student::calculateAverageScore() const {
    if (subjectScores.empty()) {
        return 0.0;
    }
    
    double sum = 0.0;
    for (const auto& [subject, score] : subjectScores) {
        sum += score;
    }
    return sum / subjectScores.size();
}

/**
 * @brief Проверяет наличие предмета у учащегося
 * @param subject Название предмета
 * @return true если предмет есть, false в противном случае
 */
bool Student::hasSubject(const std::string& subject) const {
    return subjectScores.find(subject) != subjectScores.end();
}

/**
 * @brief Очищает все данные учащегося
 */
void Student::clearData() {
    subjectScores.clear();
    subjectGrades.clear();
    averageScore = 0.0;
    rating = 0;
}