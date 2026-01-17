// ============================================
// ТЕСТ: test_grade_calculator.cpp
// Назначение: Тестирование калькулятора оценок
// ============================================

#include "doctest.h"
#include "services/GradeCalculator.hpp"

TEST_SUITE_BEGIN("GradeCalculator - Базовые тесты TDD");

/**
 * @test Первый тест TDD - проверка компиляции и минимальной функциональности
 * @details TDD итерация 1: Простейший тест для запуска цикла разработки
 */
TEST_CASE("Базовый тест компиляции") {
    SUBCASE("Метод должен компилироваться и возвращать значение") {
        // Просто проверяем, что метод можно вызвать
        int result = GradeCalculator::convertScoreToGrade(3.0);
        // Добавляем проверку, чтобы использовать переменную
        CHECK(result >= 0); // Предполагаем, что оценка неотрицательная
    }
}

TEST_SUITE_END();


TEST_SUITE_BEGIN("GradeCalculator - Точные целые значения");

TEST_CASE("Преобразование целых чисел") {
    SUBCASE("оценка 3.0 должна быть 3") {
        CHECK(GradeCalculator::convertScoreToGrade(3.0) == 3);
    }
    
    SUBCASE("оценка 2.0 должна быть 2") {
        CHECK(GradeCalculator::convertScoreToGrade(2.0) == 2);
    }
    
    SUBCASE("оценка 4.0 должна быть 4") {
        CHECK(GradeCalculator::convertScoreToGrade(4.0) == 4);
    }
    
    SUBCASE("оценка 5.0 должна быть 5") {
        CHECK(GradeCalculator::convertScoreToGrade(5.0) == 5);
    }
}

TEST_SUITE_END();

TEST_SUITE_BEGIN("GradeCalculator - Правила округления");

TEST_CASE("Округление по правилу 0.6") {
    SUBCASE("3.6 должно округляться до 4") {
        CHECK(GradeCalculator::convertScoreToGrade(3.6) == 4);
    }
    
    SUBCASE("3.4 должно округляться до 3") {
        CHECK(GradeCalculator::convertScoreToGrade(3.4) == 3);
    }
    
    SUBCASE("4.6 должно округляться до 5") {
        CHECK(GradeCalculator::convertScoreToGrade(4.6) == 5);
    }
    
    SUBCASE("4.4 должно округляться до 4") {
        CHECK(GradeCalculator::convertScoreToGrade(4.4) == 4);
    }
}

TEST_SUITE_END();

TEST_CASE("GradeCalculator - нулевые оценки") {
    SUBCASE("0.0 должно быть 0") {
        CHECK(GradeCalculator::convertScoreToGrade(0.0) == 0);
    }
    SUBCASE("0.1 должно быть 0") {
        CHECK(GradeCalculator::convertScoreToGrade(0.1) == 0);
    }
    SUBCASE("0.5 должно быть 0") {
        CHECK(GradeCalculator::convertScoreToGrade(0.5) == 0);
    }
    SUBCASE("0.9 должно быть 0") {
        CHECK(GradeCalculator::convertScoreToGrade(0.9) == 0);
    }
//    SUBCASE("1.0 должно быть 1?") {
//        CHECK(GradeCalculator::convertScoreToGrade(1.0) == 1);
//    }
}

TEST_CASE("GradeCalculator - ограничение диапазона 2-5") {
    SUBCASE("1.0 должно быть 2 (минимум)") {
        CHECK(GradeCalculator::convertScoreToGrade(1.0) == 2);
    }
    SUBCASE("1.5 должно быть 2") {
        CHECK(GradeCalculator::convertScoreToGrade(1.5) == 2);
    }
    SUBCASE("5.6 должно быть 5 (максимум)") {
        CHECK(GradeCalculator::convertScoreToGrade(5.6) == 5);
    }
    SUBCASE("6.0 должно быть 5") {
        CHECK(GradeCalculator::convertScoreToGrade(6.0) == 5);
    }
}