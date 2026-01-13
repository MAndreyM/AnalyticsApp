#include "Student.hpp"
#include <algorithm>

/**
 * @brief Проверяет, есть ли у ученика хотя бы одна двойка (оценка 2)
 * 
 * Метод проходит по всем предметам и проверяет наличие оценки 2.
 * Если ученик имеет оценку 0, он уже исключен из анализа (isExcluded == true).
 * 
 * @return true если есть хотя бы одна двойка, иначе false
 */
bool Student::hasGradeTwo() const {
    for (const auto& [subject, grade] : subjectGrades) {
        if (grade == 2) {  // Проверяем, является ли оценка двойкой
            return true;   // Нашли двойку - сразу возвращаем true
        }
    }
    return false;  // Двоек нет
}

/**
 * @brief Подсчитывает количество оценок определенного значения
 * 
 * Используется при анализе категорий:
 * - Для SINGLE_THREE: должно быть ровно одна оценка 3
 * - Для SINGLE_FOUR: должно быть ровно одна оценка 4
 * 
 * @param grade Искомая оценка (0, 2, 3, 4, 5)
 * @return int Количество предметов с указанной оценкой
 */
int Student::countGrades(int grade) const {
    int count = 0;
    for (const auto& [subject, studentGrade] : subjectGrades) {
        if (studentGrade == grade) {  // Сравниваем с искомой оценкой
            count++;  // Увеличиваем счетчик
        }
    }
    return count;
}

/**
 * @brief Получает список предметов с определенной оценкой
 * 
 * Например, если ученик имеет двойки по Математике и Физике,
 * метод вернет ["Математика", "Физика"].
 * 
 * @param grade Искомая оценка
 * @return std::vector<std::string> Список предметов с этой оценкой
 */
std::vector<std::string> Student::getSubjectsWithGrade(int grade) const {
    std::vector<std::string> subjects;
    for (const auto& [subject, studentGrade] : subjectGrades) {
        if (studentGrade == grade) {  // Нашли предмет с нужной оценкой
            subjects.push_back(subject);  // Добавляем в результат
        }
    }
    return subjects;
}

/**
 * @brief Проверяет, имеет ли ученик ровно одну оценку указанного значения
 * 
 * Используется для проверки критериев SINGLE_THREE и SINGLE_FOUR:
 * - Ровно одна тройка при остальных 4 или 5
 * - Ровно одна четверка при остальных 5
 * 
 * @param grade Искомая оценка (3 или 4 для специальных категорий)
 * @return true если ровно одна такая оценка, иначе false
 */
bool Student::hasSingleGrade(int grade) const {
    int count = 0;
    for (const auto& [subject, studentGrade] : subjectGrades) {
        if (studentGrade == grade) {  // Нашли нужную оценку
            count++;  // Увеличиваем счетчик
            if (count > 1) {  // Если нашли больше одной
                return false; // Не соответствует критерию "ровно одна"
            }
        }
    }
    return count == 1;  // Должно быть ровно одна такая оценка
}

/**
 * @brief Проверяет, содержит ли ученик только оценки из разрешенного списка
 * 
 * Используется для проверки категорий:
 * - FOURS_AND_FIVES: только оценки 4 и 5
 * - EXCELLENT: только оценки 5
 * 
 * @param allowedGrades Вектор разрешенных оценок (например, {4, 5})
 * @return true если все оценки входят в разрешенный список, иначе false
 */
bool Student::hasOnlyGrades(const std::vector<int>& allowedGrades) const {
    for (const auto& [subject, grade] : subjectGrades) {
        // Ищем оценку в списке разрешенных
        if (std::find(allowedGrades.begin(), allowedGrades.end(), grade) == allowedGrades.end()) {
            return false;  // Нашли оценку, не входящую в разрешенный список
        }
    }
    return true;  // Все оценки соответствуют критерию
}

/**
 * @brief Определяет категорию ученика согласно бизнес-правилам ТЗ
 * 
 * Алгоритм определения категории (в порядке приоритета):
 * 1. Если есть хотя бы одна оценка 0 → ZERO_GRADE (исключается из анализа)
 * 2. Если есть двойки (оценка 2) → HAS_TWOS
 * 3. Если ровно одна тройка и все остальные оценки 4 или 5 → SINGLE_THREE
 * 4. Если ровно одна четверка и все остальные оценки 5 → SINGLE_FOUR
 * 5. Если все оценки 4 или 5 (без двоек и троек) → FOURS_AND_FIVES
 * 6. Если все оценки 5 → EXCELLENT
 * 7. Во всех остальных случаях → REGULAR
 * 
 * Примечание: Ученики с оценкой 0 (ZERO_GRADE) исключаются из дальнейшего анализа
 * и не рассматриваются для категорий 2-6.
 * 
 * @return StudentCategory Категория ученика
 */
StudentCategory Student::determineCategory() const {
    // TODO: Реализовать полный алгоритм согласно ТЗ
    // Пока что возвращаем заглушку - всегда REGULAR
    
    return StudentCategory::REGULAR; // Временная заглушка
    
    // Пример структуры полной реализации:
    /*
    // 1. Проверка на наличие оценки 0
    if (hasZeroGrade) {
        return StudentCategory::ZERO_GRADE;
    }
    
    // 2. Проверка на наличие двоек
    if (hasGradeTwo()) {
        return StudentCategory::HAS_TWOS;
    }
    
    // 3. Проверка на одну тройку при остальных 4/5
    if (hasSingleGrade(3) && hasOnlyGrades({3, 4, 5})) {
        // Дополнительная проверка: остальные оценки должны быть 4 или 5
        return StudentCategory::SINGLE_THREE;
    }
    
    // 4. Проверка на одну четверку при остальных 5
    if (hasSingleGrade(4) && hasOnlyGrades({4, 5})) {
        return StudentCategory::SINGLE_FOUR;
    }
    
    // 5. Проверка на только 4 и 5
    if (hasOnlyGrades({4, 5})) {
        return StudentCategory::FOURS_AND_FIVES;
    }
    
    // 6. Проверка на только 5
    if (hasOnlyGrades({5})) {
        return StudentCategory::EXCELLENT;
    }
    
    // 7. Все остальные случаи
    return StudentCategory::REGULAR;
    */
}