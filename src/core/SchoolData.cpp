#include "SchoolData.hpp"
#include <algorithm>
#include <set>

/**
 * @brief Получает список всех доступных номеров параллелей в школе
 * 
 * Метод проходит по всем классам в schoolData и собирает уникальные номера параллелей.
 * Используется std::set для автоматического устранения дубликатов.
 * 
 * @return std::vector<int> Отсортированный список номеров параллелей (например, [2, 3, 4, ..., 11])
 */
std::vector<int> SchoolData::getAvailableGrades() const {
    std::set<int> grades;  // Используем set для автоматического удаления дубликатов
    for (const auto& [className, classData] : classes) {
        grades.insert(classData.gradeNumber);  // Добавляем номер параллели
    }
    return std::vector<int>(grades.begin(), grades.end());  // Преобразуем set в vector
}

/**
 * @brief Получает все классы определенной параллели
 * 
 * Фильтрует все классы школы, оставляя только те, которые принадлежат указанной параллели.
 * 
 * @param grade Номер параллели (2-11)
 * @return std::vector<ClassData> Список классов указанной параллели
 */
std::vector<ClassData> SchoolData::getGradeParallel(int grade) const {
    std::vector<ClassData> result;
    for (const auto& [className, classData] : classes) {
        if (classData.gradeNumber == grade) {  // Проверяем соответствие параллели
            result.push_back(classData);  // Добавляем класс в результат
        }
    }
    return result;
}

/**
 * @brief Получает названия всех классов в определенной параллели
 * 
 * Возвращает только названия классов (например, "10А", "10Б") для указанной параллели.
 * Это удобно для заполнения выпадающих списков в пользовательском интерфейсе.
 * 
 * @param grade Номер параллели
 * @return std::vector<std::string> Список названий классов
 */
std::vector<std::string> SchoolData::getClassesInGrade(int grade) const {
    std::vector<std::string> classNames;
    for (const auto& [className, classData] : classes) {
        if (classData.gradeNumber == grade) {  // Фильтруем по параллели
            classNames.push_back(className);  // Добавляем только название класса
        }
    }
    return classNames;
}

/**
 * @brief Генерирует сводную статистику по всей школе
 * 
 * TODO: Нужно реализовать полную агрегацию данных:
 * 1. Пройтись по всем классам (classes)
 * 2. Суммировать количество учащихся в каждой категории:
 *    - studentsWithZero: ученики с хотя бы одной оценкой 0
 *    - studentsWithTwos: ученики с двойками
 *    - studentsWithSingleThree: ученики с одной тройкой при остальных 4/5
 *    - studentsWithSingleFour: ученики с одной четверкой при остальных 5
 *    - studentsWithFoursAndFives: ученики, учащиеся на 4 и 5
 *    - excellentStudents: отличники (только 5)
 * 3. Вычислить общее количество учащихся (totalStudents)
 * 
 * @return SchoolSummaryView Структура с агрегированной статистикой школы
 */
SchoolSummaryView SchoolData::getSchoolSummary() const {
    // Временная заглушка - нужно реализовать полную агрегацию
    SchoolSummaryView summary;
    
    // Инициализация всех полей нулями
    summary.totalStudents = 0;
    summary.studentsWithZero = 0;
    summary.studentsWithTwos = 0;
    summary.studentsWithSingleThree = 0;
    summary.studentsWithSingleFour = 0;
    summary.studentsWithFoursAndFives = 0;
    summary.excellentStudents = 0;

    return summary; // TODO: Заменить на реальную реализацию
}