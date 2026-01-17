// ============================================
// ТЕСТ: test_grade_calculator.cpp
// Назначение: Тестирование калькулятора оценок
// ============================================

#include "doctest.h"
#include "services/GradeCalculator.hpp"

TEST_CASE("GradeCalculator - точные целые значения") {
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