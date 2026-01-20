// ============================================
// ФАЙЛ: GradeCalculator.cpp
// Реализация калькулятора оценок
// Статус: TDD этап 0 - базовый каркас
// ============================================

#include "GradeCalculator.hpp"

int GradeCalculator::convertScoreToGrade(double score) {
    // 1. Валидация входных данных
    validateScore(score);

    // 2. Специальный случай: оценка 0
    // В Дневник.ру 0 означает отсутствие оценки
    if (score < 1.0) {
        return ZERO_GRADE;
    } 
        
    // 3. Разделение на целую и дробную части
    double intPart;
    double fracPart = modf(score, &intPart);
        
    // 4. Определение округленной оценки
    int grade = static_cast<int>(intPart);
    if (shouldRoundUp(fracPart)) {
        grade += 1;
    }
        
    // 5. Применение ограничений диапазона
    return applyGradeLimits(grade);
}

bool GradeCalculator::shouldRoundUp(double fractionalPart) {
    const double EPSILON = 1e-15;  // Очень маленькое число

    return fractionalPart >= 0.6 - EPSILON;
}

int GradeCalculator::applyGradeLimits(int grade) {
    // Ограничение снизу: минимальная оценка 2
    if (grade < MIN_GRADE) {
        return MIN_GRADE;
    }
        
    // Ограничение сверху: максимальная оценка 5
    if (grade > MAX_GRADE) {
        return MAX_GRADE;
    }
        
    return grade;

}

void GradeCalculator::validateScore(double score) {
    if (score < 0.0) {
        throw std::invalid_argument(
            "Оценка не может быть отрицательной: " + std::to_string(score)
        );
    }
}