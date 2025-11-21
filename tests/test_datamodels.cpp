//#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "../src/Core/DataModels.h"

TEST_SUITE("Student Class Tests") {

    TEST_CASE("Student constructor and basic properties") {
        SUBCASE("Valid constructor") {
            Student student("Иванов Иван Иванович", "10А");
            
            CHECK(student.fullName == "Иванов Иван Иванович");
            CHECK(student.className == "10А");
            CHECK(student.averageScore == 0.0);
            CHECK(student.rating == 0);
            CHECK(student.subjectScores.empty());
            CHECK(student.subjectGrades.empty());
        }
        
        SUBCASE("Constructor with empty name should throw") {
            CHECK_THROWS_AS(Student("", "10А"), std::invalid_argument);
            CHECK_THROWS_AS(Student("Иванов Иван", ""), std::invalid_argument);
        }
    }

    TEST_CASE("Student subject management") {
        Student student("Test Student", "11Б");
        
        SUBCASE("Add valid subject score") {
            student.addSubjectScore("Математика", 4500.0);
            student.addSubjectGrade("Математика", 5);
            
            CHECK(student.hasSubject("Математика") == true);
            CHECK(student.subjectScores.at("Математика") == 4500.0);
            CHECK(student.subjectGrades.at("Математика") == 5);
        }
        
        SUBCASE("Add invalid subject score should throw") {
            CHECK_THROWS_AS(student.addSubjectScore("", 4500.0), std::invalid_argument);
            CHECK_THROWS_AS(student.addSubjectScore("Математика", -100.0), std::invalid_argument);
        }
        
        SUBCASE("Add invalid grade should throw") {
            CHECK_THROWS_AS(student.addSubjectGrade("Математика", 1), std::invalid_argument);
            CHECK_THROWS_AS(student.addSubjectGrade("Математика", 6), std::invalid_argument);
            CHECK_THROWS_AS(student.addSubjectGrade("", 5), std::invalid_argument);
        }
    }
}