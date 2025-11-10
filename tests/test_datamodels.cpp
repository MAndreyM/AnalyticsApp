//#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "DataProcessor/DataModels.h"

/*#include <doctest/doctest.h>
#include "DataProcessor/DataModels.h"*/

TEST_CASE("Student data validation") {
    SUBCASE("valid student creation") {
        Student student("10A", "Иванов Иван Иванович");
        CHECK(student.isValid() == true);
        CHECK(student.getClassName() == "10A");
        CHECK(student.getFullName() == "Иванов Иван Иванович");
        CHECK(student.getLastName() == "Иванов");
        CHECK(student.getFirstName() == "Иван");
        CHECK(student.getMiddleName() == "Иванович");
    }
    
    SUBCASE("invalid student creation") {
        CHECK_THROWS_AS(Student("", "Иванов Иван"), DataValidationException);
        CHECK_THROWS_AS(Student("10A", ""), DataValidationException);
    }
    
    SUBCASE("subject score validation") {
        Student student("10A", "Иванов Иван");
        student.addSubjectScore("Математика", 4.5);
        CHECK(student.hasSubject("Математика") == true);
        CHECK(student.getSubjectScore("Математика") == doctest::Approx(4.5));
        
        CHECK_THROWS_AS(student.addSubjectScore("", 4.5), DataValidationException);
        CHECK_THROWS_AS(student.addSubjectScore("Физика", -1.0), DataValidationException);
        CHECK_THROWS_AS(student.addSubjectScore("Физика", 6.0), DataValidationException);
    }
}

TEST_CASE("AnalysisResult functionality") {
    AnalysisResult result;
    
    SUBCASE("adding students") {
        Student student1("10A", "Иванов Иван");
        Student student2("10B", "Петров Петр");
        
        result.addStudentWithSingleThree("Математика", student1);
        result.addStudentWithZeroScore("Физика", student2);
        
        CHECK(result.countStudentsWithSingleThree() == 1);
        CHECK(result.countStudentsWithZeroScore() == 1);
        
        const auto& singleThree = result.getStudentsWithSingleThree();
        const auto& zeroScore = result.getStudentsWithZeroScore();
        
        CHECK(singleThree[0].first == "Математика");
        CHECK(singleThree[0].second.getFullName() == "Иванов Иван");
        CHECK(zeroScore[0].first == "Физика");
        CHECK(zeroScore[0].second.getFullName() == "Петров Петр");
    }
    
    SUBCASE("clearing results") {
        Student student("10A", "Иванов Иван");
        result.addStudentWithSingleThree("Математика", student);
        result.addStudentWithZeroScore("Физика", student);
        
        CHECK(result.countStudentsWithSingleThree() == 1);
        CHECK(result.countStudentsWithZeroScore() == 1);
        
        result.clear();
        
        CHECK(result.countStudentsWithSingleThree() == 0);
        CHECK(result.countStudentsWithZeroScore() == 0);
    }
}

TEST_CASE("Student subject grades functionality") {
    Student student("10A", "Иванов Иван Иванович");
    
    SUBCASE("set and get subject grades") {
        student.addSubjectScore("Математика", 4.5);
        student.setSubjectGrade("Математика", 5);
        
        CHECK(student.getSubjectGrade("Математика") == 5);
        CHECK(student.hasSubject("Математика") == true);
    }
    
    SUBCASE("grade validation") {
        CHECK_THROWS_AS(student.setSubjectGrade("", 4), DataValidationException);
        CHECK_THROWS_AS(student.setSubjectGrade("Физика", 1), DataValidationException);
        CHECK_THROWS_AS(student.setSubjectGrade("Физика", 6), DataValidationException);
    }
    
    SUBCASE("get non-existent grade throws exception") {
        CHECK_THROWS_AS(student.getSubjectGrade("Несуществующий предмет"), DataValidationException);
    }
}