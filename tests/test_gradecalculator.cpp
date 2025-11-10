#include <doctest/doctest.h>
#include "DataProcessor/GradeCalculator.h"
#include "DataProcessor/DataModels.h"
#include <algorithm>

// Вспомогательная функция для создания тестовых студентов
Student createTestStudent(const std::string& name, const std::vector<std::pair<std::string, double>>& subjects) {
    Student student("10A", name);
    for (const auto& [subject, score] : subjects) {
        student.addSubjectScore(subject, score);
    }
    return student;
}

TEST_CASE("GradeCalculator basic functionality") {
    GradeCalculator calculator;
    
    SUBCASE("grade calculation rules") {
        CHECK(calculator.calculateGrade(3.6) == 4);
        CHECK(calculator.calculateGrade(3.75) == 4);
        CHECK(calculator.calculateGrade(4.55) == 4);
        CHECK(calculator.calculateGrade(2.3) == 2);
        CHECK(calculator.calculateGrade(4.59) == 4);
        CHECK(calculator.calculateGrade(0.0) == 2);
        CHECK(calculator.calculateGrade(5.9) == 5);
    }
    
    SUBCASE("calculateAllGrades sets subject grades") {
        Student student = createTestStudent("Иванов Иван", {
            {"Математика", 3.6}, 
            {"Физика", 4.55}, 
            {"Химия", 2.3}
        });
        
        calculator.calculateAllGrades(student);
        
        CHECK(student.getSubjectGrade("Математика") == 4);
        CHECK(student.getSubjectGrade("Физика") == 4);
        CHECK(student.getSubjectGrade("Химия") == 2);
    }
}

TEST_CASE("Test scenario 1: Class without single three and zero scores") {
    GradeCalculator calculator;
    
    std::vector<Student> students = {
        createTestStudent("Иванов Иван Иванович", {
            {"Математика", 4.5}, {"Физика", 4.0}, {"Химия", 5.0}, {"Литература", 4.8}
        }),
        createTestStudent("Петров Петр Петрович", {
            {"Математика", 3.8}, {"Физика", 4.2}, {"Химия", 4.5}, {"Литература", 4.0}
        }),
        createTestStudent("Сидоров Алексей Владимирович", {
            {"Математика", 5.0}, {"Физика", 4.8}, {"Химия", 4.9}, {"Литература", 5.0}
        })
    };
    
    AnalysisResult result = calculator.analyzeClass(students);
    
    SUBCASE("no students with single three") {
        CHECK(result.countStudentsWithSingleThree() == 0);
    }
    
    SUBCASE("no students with zero score") {
        CHECK(result.countStudentsWithZeroScore() == 0);
    }
}

TEST_CASE("Test scenario 2: Class with single three and multiple threes") {
    GradeCalculator calculator;
    
    std::vector<Student> students = {
        // Одна тройка (3.4 → 3)
        createTestStudent("Кузнецова Анна Сергеевна", {
            {"Математика", 3.4}, {"Физика", 4.2}, {"Химия", 4.5}, {"Литература", 4.8}
        }),
        // Две тройки (3.2 → 3, 3.5 → 3)
        createTestStudent("Смирнов Дмитрий Олегович", {
            {"Математика", 3.2}, {"Физика", 3.5}, {"Химия", 4.5}, {"Литература", 4.0}
        }),
        // Одна тройка (3.59 → 3) ← ИСПРАВЛЕНО: было 3.6 → 4
        createTestStudent("Федорова Мария Александровна", {
            {"Математика", 4.5}, {"Физика", 3.59}, {"Химия", 4.9}, {"Литература", 4.7}
        }),
        // Без троек
        createTestStudent("Николаев Андрей Викторович", {
            {"Математика", 4.8}, {"Физика", 4.2}, {"Химия", 4.5}, {"Литература", 4.9}
        })
    };
    
    AnalysisResult result = calculator.analyzeClass(students);
    
    SUBCASE("correct count of students with single three") {
        CHECK(result.countStudentsWithSingleThree() == 2);
    }
    
    SUBCASE("correct students identified") {
        const auto& singleThree = result.getStudentsWithSingleThree();
        REQUIRE(singleThree.size() == 2);
        
        // Проверяем, что правильные студенты найдены
        std::vector<std::string> expectedNames = {
            "Кузнецова Анна Сергеевна",
            "Федорова Мария Александровна"
        };
        
        for (const auto& name : expectedNames) {
            bool found = std::any_of(singleThree.begin(), singleThree.end(),
                [&name](const auto& pair) { return pair.second.getFullName() == name; });
            CHECK(found == true);
        }
    }
    
    SUBCASE("student with multiple threes not included") {
        const auto& singleThree = result.getStudentsWithSingleThree();
        bool hasSmirnov = std::any_of(singleThree.begin(), singleThree.end(),
            [](const auto& pair) { return pair.second.getFullName() == "Смирнов Дмитрий Олегович"; });
        CHECK(hasSmirnov == false);
    }
    
    SUBCASE("correct subjects identified for single three") {
        const auto& singleThree = result.getStudentsWithSingleThree();
        
        // Находим предметы для каждого студента
        std::string kuznetsovaSubject;
        std::string fedorovaSubject;
        
        for (const auto& [subject, student] : singleThree) {
            if (student.getFullName() == "Кузнецова Анна Сергеевна") {
                kuznetsovaSubject = subject;
            } else if (student.getFullName() == "Федорова Мария Александровна") {
                fedorovaSubject = subject;
            }
        }
        
        CHECK(kuznetsovaSubject == "Математика");
        CHECK(fedorovaSubject == "Физика");
    }
}

TEST_CASE("Test scenario 3: Class with zero scores") {
    GradeCalculator calculator;
    
    std::vector<Student> students = {
        createTestStudent("Васильев Олег Николаевич", {
            {"Математика", 4.5}, {"Физика", 0.0}, {"Химия", 4.5}, {"Литература", 4.2}
        }),
        createTestStudent("Павлова Елена Дмитриевна", {
            {"Математика", 3.8}, {"Физика", 4.2}, {"Химия", 0.0}, {"Литература", 4.0}
        }),
        createTestStudent("Григорьев Игорь Станиславович", {
            {"Математика", 5.0}, {"Физика", 4.8}, {"Химия", 4.9}, {"Литература", 5.0}
        }),
        createTestStudent("Тихонова Светлана Владимировна", {
            {"Математика", 0.0}, {"Физика", 4.5}, {"Химия", 4.2}, {"Литература", 4.8}
        })
    };
    
    AnalysisResult result = calculator.analyzeClass(students);
    
    SUBCASE("correct count of students with zero score") {
        CHECK(result.countStudentsWithZeroScore() == 3);
    }
    
    SUBCASE("correct subjects identified") {
        const auto& zeroScore = result.getStudentsWithZeroScore();
        
        // Проверяем, что все студенты с нулевыми баллами найдены
        std::vector<std::string> expectedNames = {
            "Васильев Олег Николаевич",
            "Павлова Елена Дмитриевна", 
            "Тихонова Светлана Владимировна"
        };
        
        for (const auto& name : expectedNames) {
            bool found = std::any_of(zeroScore.begin(), zeroScore.end(),
                [&name](const auto& pair) { return pair.second.getFullName() == name; });
            CHECK(found == true);
        }
    }
    
    SUBCASE("student without zero scores not included") {
        const auto& zeroScore = result.getStudentsWithZeroScore();
        bool hasGrigoriev = std::any_of(zeroScore.begin(), zeroScore.end(),
            [](const auto& pair) { return pair.second.getFullName() == "Григорьев Игорь Станиславович"; });
        CHECK(hasGrigoriev == false);
    }
}

TEST_CASE("Test scenario 4: Class with single three and zero score") {
    GradeCalculator calculator;
    
    std::vector<Student> students = {
        // Одна тройка + нулевой балл
        createTestStudent("Белов Артем Юрьевич", {
            {"Математика", 3.4}, {"Физика", 0.0}, {"Химия", 4.5}, {"Литература", 4.2}
        }),
        // Только нулевой балл
        createTestStudent("Ковалева Юлия Андреевна", {
            {"Математика", 4.5}, {"Физика", 4.2}, {"Химия", 0.0}, {"Литература", 4.0}
        }),
        // Одна тройка
        createTestStudent("Орлов Максим Сергеевич", {
            {"Математика", 4.5}, {"Физика", 3.6}, {"Химия", 4.9}, {"Литература", 4.7}
        }),
        // Одна тройка + нулевой балл
        createTestStudent("Зайцева Ольга Викторовна", {
            {"Математика", 3.5}, {"Физика", 4.2}, {"Химия", 0.0}, {"Литература", 4.8}
        }),
        // Две тройки (не должен попасть в single three)
        createTestStudent("Морозов Александр Игоревич", {
            {"Математика", 3.4}, {"Физика", 3.2}, {"Химия", 4.1}, {"Литература", 4.3}
        })
    };
    
    AnalysisResult result = calculator.analyzeClass(students);
    
    SUBCASE("correct counts for both criteria") {
        CHECK(result.countStudentsWithSingleThree() == 3); // Белов, Орлов, Зайцева
        CHECK(result.countStudentsWithZeroScore() == 3);   // Белов, Ковалева, Зайцева
    }
    
    SUBCASE("students appear in both lists if applicable") {
        const auto& singleThree = result.getStudentsWithSingleThree();
        const auto& zeroScore = result.getStudentsWithZeroScore();
        
        // Белов должен быть в обоих списках
        bool belovInSingleThree = std::any_of(singleThree.begin(), singleThree.end(),
            [](const auto& pair) { return pair.second.getFullName() == "Белов Артем Юрьевич"; });
        bool belovInZeroScore = std::any_of(zeroScore.begin(), zeroScore.end(),
            [](const auto& pair) { return pair.second.getFullName() == "Белов Артем Юрьевич"; });
            
        CHECK(belovInSingleThree == true);
        CHECK(belovInZeroScore == true);
        
        // Зайцева должна быть в обоих списках
        bool zaitsevaInSingleThree = std::any_of(singleThree.begin(), singleThree.end(),
            [](const auto& pair) { return pair.second.getFullName() == "Зайцева Ольга Викторовна"; });
        bool zaitsevaInZeroScore = std::any_of(zeroScore.begin(), zeroScore.end(),
            [](const auto& pair) { return pair.second.getFullName() == "Зайцева Ольга Викторовна"; });
            
        CHECK(zaitsevaInSingleThree == true);
        CHECK(zaitsevaInZeroScore == true);
    }
    
    SUBCASE("student with multiple threes not in single three list") {
        const auto& singleThree = result.getStudentsWithSingleThree();
        bool hasMorozov = std::any_of(singleThree.begin(), singleThree.end(),
            [](const auto& pair) { return pair.second.getFullName() == "Морозов Александр Игоревич"; });
        CHECK(hasMorozov == false);
    }
}