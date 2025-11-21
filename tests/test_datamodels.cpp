//#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "../src/Core/DataModels.h"
#include <stdexcept>

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
        
        SUBCASE("Check subject existence") {
            CHECK(student.hasSubject("Несуществующий предмет") == false);
            student.addSubjectScore("Физика", 4000.0);
            CHECK(student.hasSubject("Физика") == true);
        }
    }

    TEST_CASE("Student average score calculation") {
        SUBCASE("Calculate average with multiple subjects") {
            Student student("Test Student", "9В");
            student.addSubjectScore("Физика", 4000.0);
            student.addSubjectScore("Химия", 3500.0);
            student.addSubjectScore("Биология", 4500.0);
            
            double average = student.calculateAverageScore();
            CHECK(average == doctest::Approx(4000.0)); // (4000 + 3500 + 4500) / 3 = 4000
        }
        
        SUBCASE("Empty average score") {
            Student student("Test Student", "9В");
            CHECK(student.calculateAverageScore() == 0.0);
        }
        
        SUBCASE("Single subject average") {
            Student student("Test Student", "9В");
            student.addSubjectScore("Математика", 5000.0);
            CHECK(student.calculateAverageScore() == 5000.0);
        }
    }

    TEST_CASE("Student data cleanup") {
        Student student("Test Student", "10А");
        student.addSubjectScore("Математика", 4500.0);
        student.addSubjectGrade("Математика", 5);
        student.averageScore = 4.5;
        student.rating = 1;
        
        SUBCASE("Check initial state") {
            CHECK_FALSE(student.subjectScores.empty());
            CHECK_FALSE(student.subjectGrades.empty());
            CHECK(student.averageScore == 4.5);
            CHECK(student.rating == 1);
        }
        
        SUBCASE("After cleanup") {
            student.clearData();
            
            CHECK(student.subjectScores.empty());
            CHECK(student.subjectGrades.empty());
            CHECK(student.averageScore == 0.0);
            CHECK(student.rating == 0);
        }
    }

    TEST_CASE("Student serialization") {
        Student student("Петров Петр Петрович", "11А");
        student.addSubjectScore("Математика", 4800.0);
        student.averageScore = 4.8;
        student.rating = 3;
        
        std::string result = student.toString();
        
        CHECK(result.find("Петров Петр Петрович") != std::string::npos);
        CHECK(result.find("11А") != std::string::npos);
        CHECK(result.find("4.8") != std::string::npos);
        CHECK(result.find("3") != std::string::npos);
    }
}