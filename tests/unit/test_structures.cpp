// tests/unit/test_structures.cpp - НАЧАЛЬНЫЙ ФАЙЛ
#include "doctest.h"

// ВАЖНО: Пока НЕ включаем наши заголовки - будем добавлять постепенно
#include "../src/core/StudentCategory.hpp"
#include "../src/parsers/FileMetadata.hpp"
#include "../src/core/SchoolSummaryView.hpp"
#include "../src/core/Student.hpp"
#include "../src/core/ClassData.hpp"
#include "../src/core/SchoolData.hpp"

#include <unordered_map>


TEST_SUITE("StudentCategory Enum") {
    TEST_CASE("Enum values exist") {
        // Просто проверяем, что можем использовать enum
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

TEST_SUITE("SchoolSummaryView Structure") {
    TEST_CASE("Equality operator") {
        SchoolSummaryView a{100, 5, 3, 2, 1, 20, 10};
        SchoolSummaryView b{100, 5, 3, 2, 1, 20, 10};
        SchoolSummaryView c{101, 5, 3, 2, 1, 20, 10}; // Отличается

        CHECK(a == b);
        CHECK_FALSE(a == c);
        CHECK(a != c);
    }

    TEST_CASE("Default initialization") {
        SchoolSummaryView view;
        // Проверяем, что можем создать (типы правильные)
        view.totalStudents = 10;
        CHECK(view.totalStudents == 10);
    }
}

TEST_SUITE("Student Structure") {
    TEST_CASE("Student can be created") {
        Student student;
        student.fullName = "Иванов Иван Иванович";
        student.className = "10А";
        student.hasZeroGrade = false;

        CHECK(student.fullName == "Иванов Иван Иванович");
        CHECK(student.className == "10А");
        CHECK(student.hasZeroGrade == false);
    }

    TEST_CASE("Student with grades map") {
        Student student;
        student.subjectGrades = {
            {"Математика", 4},
            {"Физика", 5}
        };

        CHECK(student.subjectGrades.size() == 2);
        CHECK(student.subjectGrades["Математика"] == 4);
    }

        TEST_CASE("Student::hasGradeTwo() basic functionality") {
        Student student;

        SUBCASE("Student without grade 2") {
            student.subjectGrades = {{"Математика", 4}, {"Физика", 5}};
            CHECK(student.hasGradeTwo() == false);
        }

        SUBCASE("Student with grade 2") {
            student.subjectGrades = {{"Математика", 2}, {"Физика", 5}};
            CHECK(student.hasGradeTwo() == true);
        }

        SUBCASE("Empty grades map") {
            student.subjectGrades = {};
            CHECK(student.hasGradeTwo() == false);
        }
    }

    TEST_CASE("Student::countGrades()") {
        Student student;
        student.subjectGrades = {
            {"Математика", 4},
            {"Физика", 5},
            {"Химия", 4},
            {"История", 3},
            {"Литература", 4}
        };

        CHECK(student.countGrades(4) == 3);
        CHECK(student.countGrades(5) == 1);
        CHECK(student.countGrades(3) == 1);
        CHECK(student.countGrades(2) == 0);
        CHECK(student.countGrades(0) == 0);
    }

    TEST_CASE("Student::getSubjectsWithGrade()") {
        Student student;
        student.subjectGrades = {
            {"Математика", 4},
            {"Физика", 5},
            {"Химия", 4},
            {"История", 3}
        };

        auto subjectsWith4 = student.getSubjectsWithGrade(4);
        CHECK(subjectsWith4.size() == 2);
        CHECK(std::find(subjectsWith4.begin(), subjectsWith4.end(), "Математика") != subjectsWith4.end());

        auto subjectsWith5 = student.getSubjectsWithGrade(5);
        CHECK(subjectsWith5.size() == 1);
        CHECK(subjectsWith5[0] == "Физика");
    }

    TEST_CASE("Student::hasGradeTwo()") {
        Student student;

        SUBCASE("Student without grade 2") {
            student.subjectGrades = {{"Математика", 4}, {"Физика", 5}};
            CHECK(student.hasGradeTwo() == false);
        }

        SUBCASE("Student with one grade 2") {
            student.subjectGrades = {{"Математика", 2}, {"Физика", 5}};
            CHECK(student.hasGradeTwo() == true);
        }

        SUBCASE("Student with multiple grade 2") {
            student.subjectGrades = {{"Математика", 2}, {"Физика", 2}, {"Химия", 3}};
            CHECK(student.hasGradeTwo() == true);
        }

        SUBCASE("Empty grades") {
            student.subjectGrades = {};
            CHECK(student.hasGradeTwo() == false);
        }
    }

    TEST_CASE("Student::hasSingleGrade()") {
        Student student;
        student.subjectGrades = {{"Математика", 4}, {"Физика", 4}, {"Химия", 5}};

        CHECK(student.hasSingleGrade(4) == false); // Две четверки
        CHECK(student.hasSingleGrade(5) == true);  // Одна пятерка
        CHECK(student.hasSingleGrade(3) == false); // Нет троек
        CHECK(student.hasSingleGrade(2) == false); // Нет двоек
    }

    TEST_CASE("Student::hasOnlyGrades()") {
        Student student;

        SUBCASE("All grades in allowed list") {
            student.subjectGrades = {{"Математика", 4}, {"Физика", 5}};
            CHECK(student.hasOnlyGrades({4, 5}) == true);
        }

        SUBCASE("One grade not in allowed list") {
            student.subjectGrades = {{"Математика", 4}, {"Физика", 3}};
            CHECK(student.hasOnlyGrades({4, 5}) == false);
        }

        SUBCASE("Empty grades") {
            student.subjectGrades = {};
            CHECK(student.hasOnlyGrades({4, 5}) == true);
        }
    }

    TEST_CASE("Student::determineCategory() placeholder") {
        Student student;
        // TODO: Заменить на реальные тесты после реализации determineCategory()
        student.category = student.determineCategory();
        CHECK(true); // Просто проверяем, что метод вызывается без ошибок
    }
}

TEST_SUITE("ClassData Structure") {
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

        Student s1, s2, s3;
        s1.fullName = "Иванов И.И.";
        s2.fullName = "Петров П.П.";
        s3.fullName = "Сидоров С.С.";

        classData.students = {s1, s2, s3};

        CHECK(classData.getTotalStudents() == 3);
    }

    TEST_CASE("ClassData::getAnalyzedStudents()") {
        ClassData classData;

        Student s1, s2, s3;
        classData.students = {s1, s2, s3};

        SUBCASE("No zero grades") {
            CHECK(classData.getAnalyzedStudents() == 3);
        }

        SUBCASE("Some zero grades") {
            classData.studentsWithZero = {s1};
            CHECK(classData.getAnalyzedStudents() == 2);
        }
    }

}

TEST_SUITE("SchoolData Structure") {
    TEST_CASE("Empty school") {
        SchoolData school;
        auto grades = school.getAvailableGrades();
        CHECK(grades.empty());
        CHECK(school.getClasses().empty());
    }
    
    TEST_CASE("Available grades calculation") {
        SchoolData school;
        
        ClassData class10A;
        class10A.gradeNumber = 10;
        class10A.className = "10А";
        
        ClassData class10B;
        class10B.gradeNumber = 10;
        class10B.className = "10Б";
        
        ClassData class11A;
        class11A.gradeNumber = 11;
        class11A.className = "11А";
        
        // Используем новый метод для добавления данных
        school.addOrUpdateClass("10А", class10A);
        school.addOrUpdateClass("10Б", class10B);
        school.addOrUpdateClass("11А", class11A);
        
        auto grades = school.getAvailableGrades();
        CHECK(grades.size() == 2); // 10 и 11
        CHECK(std::find(grades.begin(), grades.end(), 10) != grades.end());
        CHECK(std::find(grades.begin(), grades.end(), 11) != grades.end());
    }
    
    TEST_CASE("Get grade parallel") {
        SchoolData school;
        
        ClassData class10A;
        class10A.gradeNumber = 10;
        class10A.className = "10А";
        
        ClassData class10B;
        class10B.gradeNumber = 10;
        class10B.className = "10Б";
        
        ClassData class11A;
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

        // Используем addOrUpdateClass вместо прямого доступа к classes
        schoolData.addOrUpdateClass("10А", class10A);
        schoolData.addOrUpdateClass("10Б", class10B);
        schoolData.addOrUpdateClass("11А", class11A);

        // Теперь используем существующий метод getClassesInGrade()
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
        // TODO: Заменить на реальные тесты после реализации getSchoolSummary()
        auto summary = schoolData.getSchoolSummary();
        CHECK(summary.totalStudents == 0); // Проверяем, что заглушка работает
    }
}