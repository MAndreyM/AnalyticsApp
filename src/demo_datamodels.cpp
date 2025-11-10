#include <iostream>
#include <iomanip>
#include <vector>
#include "DataModels.h"
#include "GradeCalculator.h"

/**
 * @brief Создает тестовые данные для всех сценариев
 */
std::vector<std::pair<std::string, std::vector<Student>>> createTestScenarios() {
    std::vector<std::pair<std::string, std::vector<Student>>> scenarios;
    
    // Сценарий 1: Класс без одной тройки и без нулевых баллов
    std::vector<Student> scenario1 = {
        createStudent("10A", "Иванов Иван Иванович", {
            {"Математика", 4.5}, {"Физика", 4.0}, {"Химия", 5.0}, {"Литература", 4.8}
        }),
        createStudent("10A", "Петров Петр Петрович", {
            {"Математика", 3.8}, {"Физика", 4.2}, {"Химия", 4.5}, {"Литература", 4.0}
        }),
        createStudent("10A", "Сидоров Алексей Владимирович", {
            {"Математика", 5.0}, {"Физика", 4.8}, {"Химия", 4.9}, {"Литература", 5.0}
        })
    };
    scenarios.emplace_back("Класс без одной тройки и без нулевых баллов", scenario1);
    
    // Сценарий 2: Класс с одной тройкой и двумя тройками
    std::vector<Student> scenario2 = {
        createStudent("10B", "Кузнецова Анна Сергеевна", {
            {"Математика", 3.4}, {"Физика", 4.2}, {"Химия", 4.5}, {"Литература", 4.8}
        }),
        createStudent("10B", "Смирнов Дмитрий Олегович", {
            {"Математика", 3.2}, {"Физика", 3.5}, {"Химия", 4.5}, {"Литература", 4.0}
        }),
        createStudent("10B", "Федорова Мария Александровна", {
            {"Математика", 4.5}, {"Физика", 3.6}, {"Химия", 4.9}, {"Литература", 4.7}
        }),
        createStudent("10B", "Николаев Андрей Викторович", {
            {"Математика", 4.8}, {"Физика", 4.2}, {"Химия", 4.5}, {"Литература", 4.9}
        })
    };
    scenarios.emplace_back("Класс с одной тройкой и двумя тройками", scenario2);
    
    // Сценарий 3: Класс с нулевыми баллами
    std::vector<Student> scenario3 = {
        createStudent("10C", "Васильев Олег Николаевич", {
            {"Математика", 4.5}, {"Физика", 0.0}, {"Химия", 4.5}, {"Литература", 4.2}
        }),
        createStudent("10C", "Павлова Елена Дмитриевна", {
            {"Математика", 3.8}, {"Физика", 4.2}, {"Химия", 0.0}, {"Литература", 4.0}
        }),
        createStudent("10C", "Григорьев Игорь Станиславович", {
            {"Математика", 5.0}, {"Физика", 4.8}, {"Химия", 4.9}, {"Литература", 5.0}
        }),
        createStudent("10C", "Тихонова Светлана Владимировна", {
            {"Математика", 0.0}, {"Физика", 4.5}, {"Химия", 4.2}, {"Литература", 4.8}
        })
    };
    scenarios.emplace_back("Класс с нулевыми баллами", scenario3);
    
    // Сценарий 4: Класс с одной тройкой и нулевыми баллами
    std::vector<Student> scenario4 = {
        createStudent("10D", "Белов Артем Юрьевич", {
            {"Математика", 3.4}, {"Физика", 0.0}, {"Химия", 4.5}, {"Литература", 4.2}
        }),
        createStudent("10D", "Ковалева Юлия Андреевна", {
            {"Математика", 4.5}, {"Физика", 4.2}, {"Химия", 0.0}, {"Литература", 4.0}
        }),
        createStudent("10D", "Орлов Максим Сергеевич", {
            {"Математика", 4.5}, {"Физика", 3.6}, {"Химия", 4.9}, {"Литература", 4.7}
        }),
        createStudent("10D", "Зайцева Ольга Викторовна", {
            {"Математика", 3.5}, {"Физика", 4.2}, {"Химия", 0.0}, {"Литература", 4.8}
        }),
        createStudent("10D", "Морозов Александр Игоревич", {
            {"Математика", 3.4}, {"Физика", 3.2}, {"Химия", 4.1}, {"Литература", 4.3}
        })
    };
    scenarios.emplace_back("Класс с одной тройкой и нулевыми баллами", scenario4);
    
    return scenarios;
}

/**
 * @brief Выводит результаты анализа в требуемом формате
 */
void printAnalysisResults(const AnalysisResult& result, const std::string& className) {
    const auto& singleThree = result.getStudentsWithSingleThree();
    const auto& zeroScore = result.getStudentsWithZeroScore();
    
    // Учащиеся с одной тройкой
    if (!singleThree.empty()) {
        std::cout << "------" << std::endl;
        std::cout << className << std::endl;
        for (const auto& [subject, student] : singleThree) {
            std::cout << subject << " <-> " << student.getFullName() << std::endl;
        }
    }
    
    // Учащиеся с нулевым баллом
    if (!zeroScore.empty()) {
        std::cout << "------" << std::endl;
        std::cout << className << std::endl;
        for (const auto& [subject, student] : zeroScore) {
            std::cout << subject << " <-> " << student.getFullName() << std::endl;
        }
    }
}

/**
 * @brief Анализирует все тестовые сценарии
 */
void analyzeAllScenarios() {
    std::cout << "АНАЛИЗ УСПЕВАЕМОСТИ УЧАЩИХСЯ" << std::endl;
    std::cout << "============================" << std::endl << std::endl;
    
    GradeCalculator calculator;
    auto scenarios = createTestScenarios();
    
    for (const auto& [scenarioName, students] : scenarios) {
        std::cout << "Сценарий: " << scenarioName << std::endl;
        
        if (!students.empty()) {
            std::string className = students[0].getClassName();
            AnalysisResult result = calculator.analyzeClass(students);
            printAnalysisResults(result, className);
        }
        
        std::cout << std::endl;
    }
    
    // Сводная статистика
    std::cout << "======= СВОДНАЯ СТАТИСТИКА =======" << std::endl;
    for (const auto& [scenarioName, students] : scenarios) {
        if (!students.empty()) {
            std::string className = students[0].getClassName();
            AnalysisResult result = calculator.analyzeClass(students);
            
            std::cout << className << ": " 
                      << result.countStudentsWithSingleThree() << " уч. с одной тройкой, "
                      << result.countStudentsWithZeroScore() << " уч. с нулевым баллом"
                      << std::endl;
        }
    }
}

int main() {
    try {
        analyzeAllScenarios();
        std::cout << std::endl << "Анализ завершен успешно!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}