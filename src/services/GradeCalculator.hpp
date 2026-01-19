// ============================================
// ФАЙЛ: GradeCalculator.hpp
// Назначение: Преобразование десятичных баллов в пятибалльные оценки
// Статус: TDD этап 0 - базовый каркас
// ============================================

#pragma once

#include <cmath>
#include <string>
#include <stdexcept>

/**
 * @class GradeCalculator
 * @brief Калькулятор для преобразования баллов в оценки по правилам Дневник.ру
 * 
 * Правила преобразования (будут реализованы в следующих итерациях TDD):
 * - Дробная часть ≥ 0.6 → округление в большую сторону
 * - Дробная часть < 0.6 → округление в меньшую сторону
 * - Оценка 0 остаётся 0 (отсутствие оценки)
 * - Итоговая оценка ограничена диапазоном 2-5 (кроме оценки 0)
 */
class GradeCalculator {
private:
    // Константы для правил округления
    static constexpr double ROUNDUP_THRESHOLD = 0.6;
    static constexpr int MIN_GRADE = 2;
    static constexpr int MAX_GRADE = 5;
    static constexpr int ZERO_GRADE = 0;

    /**
     * @brief Валидирует входной балл
     * 
     * @param score Проверяемый балл
     * @throws std::invalid_argument Если балл отрицательный
     */
    static void validateScore(double score) {
        if (score < 0.0) {
            throw std::invalid_argument(
                "Оценка не может быть отрицательной: " + std::to_string(score)
            );
        }
    }

    /**
     * @brief Применяет ограничения к оценке
     * 
     * @param grade Оценка до применения ограничений
     * @return int Оценка в диапазоне MIN_GRADE-MAX_GRADE
     */
    static int applyGradeLimits(int grade) {
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
public:
    /**
     * @brief Проверяет, нужно ли округлять в большую сторону
     * 
     * @param fractionalPart Дробная часть балла (0.0 - 0.999...)
     * @return true если дробная часть ≥ 0.6
     * @return false если дробная часть < 0.6
     */
    static bool shouldRoundUp(double fractionalPart) {
        const double EPSILON = 1e-10;  // Очень маленькое число

        return fractionalPart >= 0.6 - EPSILON;
    }

    /**
     * @brief Преобразует десятичный балл в пятибалльную оценку
     * @param score Десятичный балл от 0.0 до 5.0
     * @return int Оценка: 0 или от 2 до 5
     * 
     * @note Метод будет реализован в процессе TDD
     * @todo Реализовать алгоритм преобразования
     */
    static int convertScoreToGrade(double score) {
        // 1. Валидация входных данных
        validateScore(score);

//        const double EPSILON = 1e-10;  // Очень маленькое число
        
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
};