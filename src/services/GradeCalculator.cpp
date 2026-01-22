// ============================================
// ФАЙЛ: GradeCalculator.cpp
// Реализация калькулятора оценок
// Статус: TDD этап 0 - базовый каркас
// ============================================

#include "GradeCalculator.hpp"

/**
 * @brief Преобразует десятичный балл в пятибалльную оценку
 * 
 * @param score Десятичный балл от 0.0 до 5.0
 * @return int Оценка: 0 или от 2 до 5
 * @throws std::invalid_argument Если балл отрицательный
 * 
 * @details Алгоритм работы:
 * 1. Проверка корректности входных данных
 * 2. Специальный случай: оценка меньше 1.0 считается как отсутствие оценки (0)
 * 3. Разделение балла на целую и дробную части
 * 4. Определение необходимости округления в большую сторону
 * 5. Применение ограничений диапазона (2-5)
 */
int GradeCalculator::convertScoreToGrade(double score) {
    // 1. Валидация входных данных
    validateScore(score);

    // 2. Специальный случай: оценка 0
    // В Дневник.ру 0 означает отсутствие оценки
    // Баллы < 1.0 также считаются как отсутствие оценки
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

/**
 * @brief Проверяет, нужно ли округлять в большую сторону
 * 
 * @param fractionalPart Дробная часть балла (0.0 - 0.999...)
 * @return true если дробная часть ≥ 0.6
 * @return false если дробная часть < 0.6
 * 
 * @details Использует порог 0.6 с учетом машинной точности (EPSILON)
 *          для корректного сравнения чисел с плавающей точкой
 */
bool GradeCalculator::shouldRoundUp(double fractionalPart) {
    const double EPSILON = 1e-15;  // Очень маленькое число для учета машинной точности

    return fractionalPart >= ROUNDUP_THRESHOLD - EPSILON;
}

/**
 * @brief Применяет ограничения к оценке
 * 
 * @param grade Оценка до применения ограничений
 * @return int Оценка в диапазоне MIN_GRADE-MAX_GRADE
 * 
 * @details Ограничения:
 * - Если оценка меньше MIN_GRADE (2), возвращается MIN_GRADE
 * - Если оценка больше MAX_GRADE (5), возвращается MAX_GRADE
 * - Иначе возвращается исходная оценка
 */
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

/**
 * @brief Валидирует входной балл
 * 
 * @param score Проверяемый балл
 * @throws std::invalid_argument Если балл отрицательный
 * 
 * @details Проверяет только отрицательные значения.
 *          Значения больше 5.0 корректируются в методе applyGradeLimits()
 */
void GradeCalculator::validateScore(double score) {
    if (score < 0.0) {
        throw std::invalid_argument(
            "Оценка не может быть отрицательной: " + std::to_string(score)
        );
    }
}