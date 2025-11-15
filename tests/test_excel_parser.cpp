#include <doctest/doctest.h>
#include "FileProcessor/ExcelParser.h"
#include "DataProcessor/DataModels.h"
#include "DataProcessor/GradeCalculator.h"
#include <filesystem>
#include <fstream>

TEST_SUITE("ExcelParser Unit Tests") {
    
    TEST_CASE("ExcelParser - File Validation") {
        ExcelParser parser;
        
        SUBCASE("Valid Excel file extensions") {
            CHECK(parser.isValidExcelFile("test.xls") == true);
            CHECK(parser.isValidExcelFile("test.XLS") == true);
            CHECK(parser.isValidExcelFile("file123.xls") == true);
            CHECK(parser.isValidExcelFile("teacher_report.xls") == true);
        }
        
        SUBCASE("Invalid file extensions") {
            CHECK(parser.isValidExcelFile("test.xlsx") == false);
            CHECK(parser.isValidExcelFile("test.txt") == false);
            CHECK(parser.isValidExcelFile("test.doc") == false);
            CHECK(parser.isValidExcelFile("test.pdf") == false);
            CHECK(parser.isValidExcelFile("test") == false);
        }
        
        SUBCASE("Empty and invalid paths") {
            CHECK(parser.isValidExcelFile("") == false);
            CHECK(parser.isValidExcelFile("nonexistent.xls") == false);
        }
    }
    
    TEST_CASE("ExcelParser - Class Name Extraction") {
        ExcelParser parser;
        
        SUBCASE("Standard class formats with commas") {
            CHECK(parser.extractClassName("10А, Иванов Иван") == "10А");
            CHECK(parser.extractClassName("11Б класс, Петров Петр") == "11Б класс");
            CHECK(parser.extractClassName("9В, Сидоров") == "9В");
            CHECK(parser.extractClassName("8А, Классный руководитель") == "8А");
        }
        
        SUBCASE("Class names without commas") {
            CHECK(parser.extractClassName("10А класс") == "10А класс");
            CHECK(parser.extractClassName("11Б") == "11Б");
            CHECK(parser.extractClassName("9В класс математики") == "9В класс математики");
        }
        
        SUBCASE("Edge cases and malformed input") {
            CHECK(parser.extractClassName("") == "");
            CHECK(parser.extractClassName("Просто текст") == "Просто текст");
            CHECK(parser.extractClassName(",Только запятая") == "");
            CHECK(parser.extractClassName("  10А  , С пробелами  ") == "10А");
            CHECK(parser.extractClassName("10А,") == "10А");
        }
        
        SUBCASE("Real-world examples from school reports") {
            CHECK(parser.extractClassName("10А, Иванова Мария Петровна") == "10А");
            CHECK(parser.extractClassName("11Б класс, Петров Иван Сидорович") == "11Б класс");
            CHECK(parser.extractClassName("9В, Классный руководитель: Сидорова А.П.") == "9В");
        }
    }
    
    TEST_CASE("ExcelParser - Student Data Models Integration") {
        SUBCASE("Valid student creation and validation") {
            Student student("10A", "Иванов Иван Иванович");
            student.addSubjectScore("Математика", 4.5);
            student.addSubjectScore("Физика", 3.7);
            student.addSubjectScore("Химия", 4.2);
            
            CHECK(student.isValid() == true);
            CHECK(student.getClassName() == "10A");
            CHECK(student.getFullName() == "Иванов Иван Иванович");
            CHECK(student.hasSubject("Математика") == true);
            CHECK(student.hasSubject("Физика") == true);
            CHECK(student.getSubjectScore("Математика") == doctest::Approx(4.5));
            CHECK(student.getSubjectScore("Физика") == doctest::Approx(3.7));
        }
        
        SUBCASE("Student with boundary score values") {
            Student student("11Б", "Петрова Анна");
            student.addSubjectScore("Математика", 0.0);   // Минимальный балл
            student.addSubjectScore("Литература", 5.0);   // Максимальный балл
            student.addSubjectScore("Физика", 2.5);       // Средний балл
            
            CHECK(student.isValid() == true);
            CHECK(student.getSubjectScore("Математика") == doctest::Approx(0.0));
            CHECK(student.getSubjectScore("Литература") == doctest::Approx(5.0));
        }
        
        SUBCASE("Invalid student data") {
            Student emptyStudent;
            CHECK(emptyStudent.isValid() == false);
            
            Student studentWithEmptyName("10A", "");
            CHECK(studentWithEmptyName.isValid() == false);
            
            Student studentWithInvalidScore("10A", "Сидоров");
            studentWithInvalidScore.addSubjectScore("Математика", -1.0); // Отрицательная оценка
            CHECK(studentWithInvalidScore.isValid() == false);
        }
    }
    
    TEST_CASE("ExcelParser - Error Handling") {
        ExcelParser parser;
        
        SUBCASE("Non-existent file parsing") {
            CHECK_THROWS_AS(parser.parseStudentData("nonexistent_file.xls"), std::runtime_error);
        }
        
        SUBCASE("Invalid file format parsing") {
            CHECK_THROWS_AS(parser.parseStudentData("test.txt"), std::runtime_error);
            CHECK_THROWS_AS(parser.parseStudentData("test.xlsx"), std::runtime_error);
        }
        
        SUBCASE("Directory instead of file") {
            CHECK_THROWS_AS(parser.parseStudentData("."), std::runtime_error);
            CHECK_THROWS_AS(parser.parseStudentData("./test_data"), std::runtime_error);
        }
    }
}

TEST_SUITE("ExcelParser Integration Tests") {
    
    TEST_CASE("Integration with GradeCalculator") {
        Student student("10A", "Тестовый Студент");
        student.addSubjectScore("Математика", 3.6);
        student.addSubjectScore("Физика", 4.55);
        student.addSubjectScore("Химия", 2.3);
        student.addSubjectScore("Литература", 3.75);
        
        GradeCalculator calculator;
        calculator.calculateAllGrades(student);
        
        SUBCASE("Grade calculation rules verification") {
            // 3.6 -> 4 (≥ 0.6 округляем вверх)
            CHECK(student.getSubjectGrade("Математика") == 4);
            // 4.55 -> 4 (< 0.6 округляем вниз)
            CHECK(student.getSubjectGrade("Физика") == 4);
            // 2.3 -> 2
            CHECK(student.getSubjectGrade("Химия") == 2);
            // 3.75 -> 4 (≥ 0.6 округляем вверх)
            CHECK(student.getSubjectGrade("Литература") == 4);
        }
        
        SUBCASE("Single three detection scenarios") {
            SUBCASE("Student with exactly one three") {
                Student singleThreeStudent("10B", "Одна тройка");
                singleThreeStudent.addSubjectScore("Математика", 4.5);
                singleThreeStudent.addSubjectScore("Физика", 3.2);  // Тройка
                singleThreeStudent.addSubjectScore("Химия", 4.8);
                
                CHECK(calculator.hasSingleThree(singleThreeStudent) == true);
            }
            
            SUBCASE("Student with multiple threes") {
                Student multipleThreesStudent("10B", "Много троек");
                multipleThreesStudent.addSubjectScore("Математика", 3.1);
                multipleThreesStudent.addSubjectScore("Физика", 3.4);
                multipleThreesStudent.addSubjectScore("Химия", 4.8);
                
                CHECK(calculator.hasSingleThree(multipleThreesStudent) == false);
            }
            
            SUBCASE("Student with no threes") {
                Student noThreesStudent("10B", "Без троек");
                noThreesStudent.addSubjectScore("Математика", 4.5);
                noThreesStudent.addSubjectScore("Физика", 4.2);
                noThreesStudent.addSubjectScore("Химия", 5.0);
                
                CHECK(calculator.hasSingleThree(noThreesStudent) == false);
            }
        }
        
        SUBCASE("Zero score detection") {
            SUBCASE("Student with zero score") {
                Student zeroScoreStudent("10B", "Нулевой балл");
                zeroScoreStudent.addSubjectScore("Математика", 4.5);
                zeroScoreStudent.addSubjectScore("Физика", 0.0);  // Нулевой балл
                zeroScoreStudent.addSubjectScore("Химия", 3.8);
                
                CHECK(calculator.hasZeroScore(zeroScoreStudent) == true);
            }
            
            SUBCASE("Student without zero scores") {
                Student noZeroStudent("10B", "Без нулей");
                noZeroStudent.addSubjectScore("Математика", 4.5);
                noZeroStudent.addSubjectScore("Физика", 3.2);
                noZeroStudent.addSubjectScore("Химия", 4.1);
                
                CHECK(calculator.hasZeroScore(noZeroStudent) == false);
            }
        }
    }
    
    TEST_CASE("Integration with AnalysisResult") {
        AnalysisResult result;
        Student student1("10A", "Иванов Иван");
        Student student2("10B", "Петров Петр");
        Student student3("10C", "Сидоров Сидор");
        
        // Настраиваем студентов с разными сценариями
        student1.addSubjectScore("Математика", 3.0);  // Одна тройка
        student1.addSubjectScore("Физика", 4.5);
        
        student2.addSubjectScore("Физика", 0.0);      // Нулевой балл
        student2.addSubjectScore("Химия", 4.2);
        
        student3.addSubjectScore("Математика", 3.1);  // Одна тройка
        student3.addSubjectScore("Литература", 0.0);  // И нулевой балл
        
        // Добавляем в результаты анализа
        result.addStudentWithSingleThree("Математика", student1);
        result.addStudentWithZeroScore("Физика", student2);
        result.addStudentWithSingleThree("Математика", student3);
        result.addStudentWithZeroScore("Литература", student3);
        
        SUBCASE("Result counting and structure") {
            CHECK(result.countStudentsWithSingleThree() == 2);
            CHECK(result.countStudentsWithZeroScore() == 2);
            
            CHECK(result.getStudentsWithSingleThree()[0].first == "Математика");
            CHECK(result.getStudentsWithSingleThree()[0].second.getFullName() == "Иванов Иван");
            CHECK(result.getStudentsWithSingleThree()[1].first == "Математика");
            CHECK(result.getStudentsWithSingleThree()[1].second.getFullName() == "Сидоров Сидор");
            
            CHECK(result.getStudentsWithZeroScore()[0].first == "Физика");
            CHECK(result.getStudentsWithZeroScore()[0].second.getFullName() == "Петров Петр");
            CHECK(result.getStudentsWithZeroScore()[1].first == "Литература");
            CHECK(result.getStudentsWithZeroScore()[1].second.getFullName() == "Сидоров Сидор");
        }
        
        SUBCASE("Result clearing") {
            result.clear();
            CHECK(result.countStudentsWithSingleThree() == 0);
            CHECK(result.countStudentsWithZeroScore() == 0);
        }
    }
}

TEST_SUITE("ExcelParser Real Data Structure Tests") {
    
    TEST_CASE("Expected Excel file structure") {
        ExcelParser parser;
        
        SUBCASE("Cell coordinates for real data extraction") {
            // Эти тесты определяют ожидаемую структуру реальных Excel файлов
            // и будут использоваться для реализации реальной логики парсинга
            
            // Ожидаемые координаты ячеек в реальных файлах:
            // - Ячейка A4: Название класса и ФИО классного руководителя
            // - Ячейка B2: ФИО ученика  
            // - Строки 5-15: Таблица предметов и оценок
            //   - Колонка A: Названия предметов
            //   - Колонка B: Средние баллы
            
            INFO("Real Excel files should have:");
            INFO("  - Class name in cell A4 (format: 'ClassName, Teacher Name')");
            INFO("  - Student name in cell B2");
            INFO("  - Subjects table in rows 5-15, columns A-B");
        }
        
        SUBCASE("Data validation expectations") {
            // Ожидаемые форматы данных в реальных файлах
            INFO("Expected data formats:");
            INFO("  - Class names: '10А', '11Б класс', etc.");
            INFO("  - Student names: full Russian names with spaces");
            INFO("  - Scores: floating point numbers between 0.0 and 5.0");
            INFO("  - Subject names: standard school subject names in Russian");
        }
    }
    
    TEST_CASE("Error scenarios for real Excel files") {
        ExcelParser parser;
        
        SUBCASE("Files with missing required cells") {
            INFO("Parser should handle files missing:");
            INFO("  - Cell A4 (class information)");
            INFO("  - Cell B2 (student name)");
            INFO("  - Subject table rows");
        }
        
        SUBCASE("Files with malformed data") {
            INFO("Parser should handle:");
            INFO("  - Non-numeric values in score cells");
            INFO("  - Empty subject names");
            INFO("  - Scores outside valid range (0.0-5.0)");
            INFO("  - Special characters in names");
        }
        
        SUBCASE("Files with unexpected structure") {
            INFO("Parser should be robust against:");
            INFO("  - Extra empty rows/columns");
            INFO("  - Merged cells");
            INFO("  - Different sheet names");
            INFO("  - Multiple worksheets");
        }
    }
}

// Вспомогательные функции для тестов
namespace TestHelpers {
    /**
     * @brief Создает тестового студента с реалистичными данными
     */
    Student createTestStudent(const std::string& className, const std::string& fullName) {
        Student student(className, fullName);
        
        // Добавляем типичные школьные предметы с реалистичными оценками
        student.addSubjectScore("Математика", 4.2);
        student.addSubjectScore("Русский язык", 3.8);
        student.addSubjectScore("Физика", 4.5);
        student.addSubjectScore("Химия", 3.9);
        student.addSubjectScore("Литература", 4.7);
        student.addSubjectScore("История", 4.0);
        student.addSubjectScore("Биология", 3.6);
        student.addSubjectScore("Английский язык", 4.8);
        
        return student;
    }
    
    /**
     * @brief Проверяет что студент имеет валидные данные
     */
    bool isValidStudentStructure(const Student& student) {
        return student.isValid() &&
               !student.getClassName().empty() &&
               !student.getFullName().empty() &&
               student.getSubjectScores().size() > 0;
    }
}