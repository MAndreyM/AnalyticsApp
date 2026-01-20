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

public:
    /**
     * @brief Проверяет, нужно ли округлять в большую сторону
     * 
     * @param fractionalPart Дробная часть балла (0.0 - 0.999...)
     * @return true если дробная часть ≥ 0.6
     * @return false если дробная часть < 0.6
     */
    static bool shouldRoundUp(double fractionalPart);

    /**
     * @brief Преобразует десятичный балл в пятибалльную оценку
     * @param score Десятичный балл от 0.0 до 5.0
     * @return int Оценка: 0 или от 2 до 5
     * 
     * @note Метод будет реализован в процессе TDD
     * @todo Реализовать алгоритм преобразования
     */
    static int convertScoreToGrade(double score);

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
    static void validateScore(double score);

    /**
     * @brief Применяет ограничения к оценке
     * 
     * @param grade Оценка до применения ограничений
     * @return int Оценка в диапазоне MIN_GRADE-MAX_GRADE
     */
    static int applyGradeLimits(int grade);
};