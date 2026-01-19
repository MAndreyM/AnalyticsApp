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

    static void validateScore(double score) {
        if (score < 0.0) {
            throw std::invalid_argument(
                "Оценка не может быть отрицательной: " + std::to_string(score)
            );
        }
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
        validateScore(score);

        const double EPSILON = 1e-10;  // Очень маленькое число
        
        // Особый случай: оценка меньше 1.0 = 0
        if (score < 1.0) {
            return 0;
        } 
        
        double intPart;
        double fracPart = modf(score, &intPart);
        
        int result = static_cast<int>(intPart);
        
        // Добавляем epsilon для обработки ошибок округления
        if (fracPart >= 0.6 - EPSILON) {
            result += 1;
        }
        
        // Применяем ограничения
        if (result < MIN_GRADE) {
            return MIN_GRADE;
        }
        if (result > MAX_GRADE) {
            return MAX_GRADE;
        }
        
        return result;
    }
};