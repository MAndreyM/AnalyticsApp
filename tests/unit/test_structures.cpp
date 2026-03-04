// ==============================
// ФАЙЛ: tests/unit/test_structures.cpp
// ==============================
// Тесты для структур данных (НЕ класса Student)
// ==============================

#include "doctest.h"
#include "../src/core/StudentCategory.hpp"
#include "../src/parsers/FileMetadata.hpp"
#include "../src/core/SchoolSummaryView.hpp"
#include "../src/core/ClassData.hpp"
#include "../src/core/SchoolData.hpp"

// ==============================
// ТЕСТЫ ДЛЯ StudentCategory
// ==============================
TEST_SUITE("StudentCategory Enum") {
    TEST_CASE("Enum values exist") {
        StudentCategory cat1 = StudentCategory::ZERO_GRADE;
        StudentCategory cat2 = StudentCategory::EXCELLENT;
        CHECK(static_cast<int>(cat1) != static_cast<int>(cat2));
    }

    TEST_CASE("All categories defined") {
        CHECK(static_cast<int>(StudentCategory::ZERO_GRADE) >= 0);
        CHECK(static_cast<int>(StudentCategory::HAS_TWOS) >= 0);
        CHECK(static_cast<int>(StudentCategory::SINGLE_THREE) >= 0);
        CHECK(static_cast<int>(StudentCategory::SINGLE_FOUR) >= 0);
        CHECK(static_cast<int>(StudentCategory::FOURS_AND_FIVES) >= 0);
        CHECK(static_cast<int>(StudentCategory::EXCELLENT) >= 0);
        CHECK(static_cast<int>(StudentCategory::REGULAR) >= 0);
    }
}

// ==============================
// ТЕСТЫ ДЛЯ FileMetadata
// ==============================
TEST_SUITE("FileMetadata Structure") {
    TEST_CASE("Creation and basic properties") {
        FileMetadata meta;
        meta.className = "10А";
        meta.academicYear = "2025/2026 учебный год";
        meta.exportDate = "25.12.2025";

        CHECK(meta.className == "10А");
        CHECK(meta.isValid() == true);
    }

    TEST_CASE("Validation method") {
        FileMetadata valid{"10Б", "2025/2026", "26.12.2025"};
        CHECK(valid.isValid() == true);

        FileMetadata empty;
        CHECK(empty.isValid() == false);

        FileMetadata noClass{"", "2025/2026", "26.12.2025"};
        CHECK(noClass.isValid() == false);
    }
}

// ==============================
// ТЕСТЫ ДЛЯ SchoolSummaryView
// ==============================
TEST_SUITE("SchoolSummaryView Structure") {
    TEST_CASE("Equality operator") {
        SchoolSummaryView a{100, 5, 3, 2, 1, 20, 10};
        SchoolSummaryView b{100, 5, 3, 2, 1, 20, 10};
        SchoolSummaryView c{101, 5, 3, 2, 1, 20, 10};

        CHECK(a == b);
        CHECK_FALSE(a == c);
        CHECK(a != c);
    }

    TEST_CASE("Default initialization") {
        SchoolSummaryView view;
        view.totalStudents = 10;
        CHECK(view.totalStudents == 10);
    }
}

// ==============================
// ТЕСТЫ ДЛЯ ClassData
// ==============================
/*TEST_SUITE("ClassData Structure") {
    TEST_CASE("ClassData creation") {
        ClassData classData;
        classData.className = "10А";
        classData.gradeNumber = 10;
        classData.classLetter = "А";

        CHECK(classData.className == "10А");
        CHECK(classData.gradeNumber == 10);
        CHECK(classData.getTotalStudents() == 0);
    }

    TEST_CASE("ClassData with students") {
        ClassData classData;
        // Класс содержит ссылки на студентов, но самих студентов здесь не создаем
        classData.studentRefs = {"student1", "student2", "student3"};
        CHECK(classData.getTotalStudents() == 3);
    }

    TEST_CASE("ClassData::getAnalyzedStudents()") {
        ClassData classData;
        classData.studentRefs = {"student1", "student2", "student3"};

        SUBCASE("No zero grades") {
            CHECK(classData.getAnalyzedStudents() == 3);
        }

        SUBCASE("Some zero grades") {
            classData.zeroGradeRefs = {"student1"};
            CHECK(classData.getAnalyzedStudents() == 2);
        }
    }
}
*/

// ==============================
// ТЕСТЫ ДЛЯ SchoolData
// ==============================
TEST_SUITE("SchoolData Structure") {
    TEST_CASE("Empty school") {
        SchoolData school;
        auto grades = school.getAvailableGrades();
        CHECK(grades.empty());
        CHECK(school.getClasses().empty());
    }
    
    TEST_CASE("Available grades calculation") {
        SchoolData school;
        
        ClassData class10A, class10B, class11A;
        class10A.gradeNumber = 10;
        class10A.className = "10А";
        class10B.gradeNumber = 10;
        class10B.className = "10Б";
        class11A.gradeNumber = 11;
        class11A.className = "11А";
        
        school.addOrUpdateClass("10А", class10A);
        school.addOrUpdateClass("10Б", class10B);
        school.addOrUpdateClass("11А", class11A);
        
        auto grades = school.getAvailableGrades();
        CHECK(grades.size() == 2);
        CHECK(std::find(grades.begin(), grades.end(), 10) != grades.end());
        CHECK(std::find(grades.begin(), grades.end(), 11) != grades.end());
    }
    
    TEST_CASE("Get grade parallel") {
        SchoolData school;
        
        ClassData class10A, class10B, class11A;
        class10A.gradeNumber = 10;
        class10A.className = "10А";
        class10B.gradeNumber = 10;
        class10B.className = "10Б";
        class11A.gradeNumber = 11;
        class11A.className = "11А";
        
        school.addOrUpdateClass("10А", class10A);
        school.addOrUpdateClass("10Б", class10B);
        school.addOrUpdateClass("11А", class11A);
        
        auto grade10Classes = school.getGradeParallel(10);
        CHECK(grade10Classes.size() == 2);
        
        auto grade11Classes = school.getGradeParallel(11);
        CHECK(grade11Classes.size() == 1);
        
        auto grade9Classes = school.getGradeParallel(9);
        CHECK(grade9Classes.empty());
    }

    TEST_CASE("SchoolData::getClassesInGrade()") {
        SchoolData schoolData;
        
        ClassData class10A, class10B, class11A;
        class10A.className = "10А";
        class10A.gradeNumber = 10;
        class10B.className = "10Б";
        class10B.gradeNumber = 10;
        class11A.className = "11А";
        class11A.gradeNumber = 11;

        schoolData.addOrUpdateClass("10А", class10A);
        schoolData.addOrUpdateClass("10Б", class10B);
        schoolData.addOrUpdateClass("11А", class11A);

        auto classNames10 = schoolData.getClassesInGrade(10);
        CHECK(classNames10.size() == 2);
        CHECK(std::find(classNames10.begin(), classNames10.end(), "10А") != classNames10.end());
        CHECK(std::find(classNames10.begin(), classNames10.end(), "10Б") != classNames10.end());

        auto classNames11 = schoolData.getClassesInGrade(11);
        CHECK(classNames11.size() == 1);
        CHECK(classNames11[0] == "11А");

        auto classNames9 = schoolData.getClassesInGrade(9);
        CHECK(classNames9.empty());
    }

    TEST_CASE("SchoolData::getSchoolSummary() placeholder") {
        SchoolData schoolData;
        auto summary = schoolData.getSchoolSummary();
        CHECK(summary.totalStudents == 0);
    }
}